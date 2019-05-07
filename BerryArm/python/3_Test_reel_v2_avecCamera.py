#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np

import time
import os
import sys

from pixy import *
from ctypes import *

## Parametres utilisateur:
sizePuck = 7.6

## Autres parametres:
tolerance = 4 # tolerance taille palets detectes (en cm)
d_min = [10, -15] # dist minimum par rapport a la camera
d_max = [30, 15] # dist maximum par rapport a la camera


## On récupère les données caractérisant la camera:
camera_matrix = np.loadtxt("./mesParam/camera_matrix.txt")
dist_coefs = np.loadtxt("./mesParam/dist_coefs.txt")
h = np.loadtxt("./mesParam/homography.txt")
h_inv = np.linalg.inv(h)

## Les fonctions utilises:
   
def Warppixel(h,x,y) :
    '''Prend en entree la position (x,y) d'un point dans une image subissant les effets de la perspective, ainsi que la matrice d'homographie h.
    Calcule la position du point dans la realite par homographie'''
    
    def homograph(p1,p2):   # (p1 celui de reference p2 camera)
        A = []
        i=0
        while( i< len(p1)):
            
            print(i)
            x, y = p1[i][0], p1[i][1]
            u, v = p2[i][0], p2[i][1]
            A.append([x, y, 1, 0, 0, 0, -u*x, -u*y, -u])
            A.append([0, 0, 0, x, y, 1, -v*x, -v*y, -v])
            i=i+1
        A = np.asarray(A)
        U, S, Vh = np.linalg.svd(A)
        L = Vh[-1,:] / Vh[-1,-1]
        H = L.reshape(3, 3)
        return H
        
    def C(h,x,y,i):
        res=(h[0][i-1]*y-h[1][i-1]*x)/(h[0][0]*y-h[1][0]*x)
        return res
        
    #x,y sont les coordonnees (pixel)de la camera avec la perspective
    yres=((h[1][2]-h[2][2]*y)+C(h,x,y,3)*(h[2][0]*y-h[1][0]))/((h[2][1]*y-h[1][1])+C(h,x,y,2)*(h[1][0]-h[2][0]*y))
    if(((h[2][1]*y-h[1][1])+C(h,x,y,2)*(h[1][0]-h[2][0]*y))==0):
        yres=((h[0][2]-h[2][2]*x)+C(h,x,y,3)*(h[2][0]*x-h[0][0]))/((h[2][1]*x-h[0][1])+C(h,x,y,2)*(h[0][0]-h[2][0]*x))
    xres=-(C(h,x,y,2)*yres+C(h,x,y,3))
    return(xres,yres)


def ComputeUndistortPoints(pt, camera_matrix, dist_coefs):
    '''Prend en entree la position d'un point dans l'image deformee retournee par la camera, ainsi que 2 matrices caracterisant la camera.
    Calcule la position du point dans l'image si la camera ne distort pas l'image'''
    camera_matrix_inv = np.linalg.inv(camera_matrix)
    pt_normalize = np.dot(camera_matrix_inv,pt)
    
    [k1,k2,p1,p2,k3]=dist_coefs
    xundistort,yundistort=pt_normalize[0], pt_normalize[1]
    
    for i in range(5): # Approximation des paramètres de distorsion inverse
        r2 = xundistort**2+yundistort**2
        icdist = 1 /(1 + ((k3*r2 + k2)*r2 + k1)*r2)
        deltaX = 2 * p1 * xundistort * yundistort + p2 * (r2 + 2 * xundistort**2)
        deltaY = p1 * (r2 + 2 *yundistort**2) + 2 * p2 * xundistort * yundistort
        xundistort = (pt_normalize[0] - deltaX)*icdist
        yundistort = (pt_normalize[1] - deltaY)*icdist
    
    pt_calibre = np.array([xundistort, yundistort, pt_test[-1]])
    
    pt_calibre = np.dot(camera_matrix,pt_calibre)
    
    return pt_calibre

def picture2real(pt_test, camera_matrix, dist_coefs, h_inv):
    pt_calibre=ComputeUndistortPoints(pt_test, camera_matrix, dist_coefs)
    pt_reel=Warppixel(h_inv,pt_calibre[0],pt_calibre[1])
    pt_reel = np.array([pt_reel[1],pt_reel[0]])
    return pt_reel

def isAPuck(pt_image, width_image,height_image, sizePuck,tolerance):
    '''Programme determinant si l'objet detectee est bien un palet en calculant sa taille'''
    wi_min, wi_max = pt_image[0]-width_image/2, pt_image[0]+width_image/2
    wi_min = np.array([wi_min,pt_image[1],1],dtype='float64')
    wi_max = np.array([wi_max,pt_image[1],1],dtype='float64')
    hi_min, hi_max = pt_image[1]-height_image/2, pt_image[1]+height_image/2
    hi_min = np.array([pt_image[0],hi_min,1],dtype='float64')
    hi_max = np.array([pt_image[0],hi_max,1],dtype='float64')
    
    wr_min=picture2real(wi_min, camera_matrix, dist_coefs, h_inv)
    wr_max=picture2real(wi_max, camera_matrix, dist_coefs, h_inv)
    hr_min=picture2real(hi_min, camera_matrix, dist_coefs, h_inv)
    hr_max=picture2real(hi_max, camera_matrix, dist_coefs, h_inv)
    
    w_real = np.linalg.norm(wr_max-wr_min)
    h_real = np.linalg.norm(hr_max-hr_min)
    
    if (sizePuck-tolerance < w_real < sizePuck+tolerance and sizePuck-tolerance < h_real < sizePuck+tolerance):
        return True
    
    return False
    
def manageDistance(pt_reel, d_min, d_max):  
    pt_reel_x = pt_reel[0]
    pt_reel_y = pt_reel[1]
    if ((d_min[0] < pt_reel_x < d_max[0]) and (d_min[1] < pt_reel_y < d_max[1])):
        return True
    else :
        return False
        
def managePriority(signature_list):
    nb_bleu = signature_list.count(3)
    nb_rouge = signature_list.count(2)
    if nb_bleu>0:
        return signature_list.index(3)
    if nb_rouge>0:
        return signature_list.index(2)
        
    

## Le programme

# Initialize Pixy Interpreter thread #
pixy_init()

class Blocks (Structure):
  _fields_ = [ ("type", c_uint),
               ("signature", c_uint),
               ("x", c_uint),
               ("y", c_uint),
               ("width", c_uint),
               ("height", c_uint),
               ("angle", c_uint) ]

blocks = BlockArray(100)
frame  = 0

# Wait for blocks #
#time_1 = time.time()

while 1:

  count = pixy_get_blocks(100, blocks)
  #time_2 = time.time()
  if (count > 0 ):
    signature_tab = []
    posReel_x_tab = []
    posReel_y_tab = []
    #print('J ai trouvé')
    #if (time_2-time_1>0.5):
    #time_1 = time_2
    # Blocks found #
    #print ('frame %3d:' % (frame))
    frame = frame + 1
    for index in range (0, count):
        signature = blocks[index].signature
        pos_x = blocks[index].x #- 1.5
        pos_y = blocks[index].y #- 3
        width = blocks[index].width
        height = blocks[index].height
        
        pt_test = np.array([pos_x,pos_y,1],dtype='float64')
        
        pt_reel=picture2real(pt_test, camera_matrix, dist_coefs, h_inv)
        
        pt_reel = np.array([pt_reel[0], pt_reel[1]])
        
        # a rajouter et tester : isAPuck()
        rep = isAPuck(pt_test, width,height, sizePuck,tolerance)
        rep2 = manageDistance(pt_reel,d_min,d_max)
        if rep and rep2:
            signature_tab.append(signature)
            posReel_x_tab.append(pt_reel[0])
            posReel_y_tab.append(pt_reel[1])
            #print(index, signature, pt_reel)
            
        
    indice = managePriority(signature_tab)
    if indice>-1:
        pt_reel = [posReel_x_tab[indice], posReel_y_tab[indice]]
        print >>sys.stdout, str(pt_reel[0]) + ' ' + str(pt_reel[1]) + ' ' + str(1)

    break

    

