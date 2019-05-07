#!/usr/bin/python
# -*- coding: utf-8 -*-

from math import *
import matplotlib.pyplot as plt
import sys


## Paramètres du bras
L01=7.7
L2r=2.4
L2z=10.8
L2 = sqrt(L2r**2+L2z**2)
L3=12.9
L4=3.5
L5=2.6
L6=1.3+1.7+3.0
#L5=0   #pour test camera angle=80
#L6=0
def simplify_angle(a):
    a=a%(2*pi)
    if(a>=pi):
        a=a-2*pi
    return a

def coord2D_abg(r,z,angle=0):   #donne la position de l'objet ainsi que l'angle de saisie en degre 0=horizontal 90=verticale
    '''Demande les coordonnées du point atteint par l'extrémité du bras (2D)
    Retourne les positions angulaires des angles du bras (noté alpha, beta, gamma)
    En cas d'invalidité de la position de l'extrémité du bras, une erreur se déclenche'''
    global L01, L2r, L2z, L2, L3, L4,L5,L6

    angle=50-angle
    rbis,zbis=r-L4*cos(angle*pi/180)+L5*sin(angle*pi/180)-L6*cos((angle-50)*pi/180),z-L01-L4*sin(angle*pi/180)-L5*cos(angle*pi/180)-L6*sin((angle-50)*pi/180) # origine en P2 + bras sans ventouse
    Dcarre=rbis**2+zbis**2 # distance origine->extrémité du bras
    cte1 = atan2(L2z,L2r)
    if(abs((Dcarre-(L2**2+L3**2))/(2*L2*L3))<1):
        # Calcul de beta
        beta=-acos((Dcarre-(L2**2+L3**2))/(2*L2*L3))+cte1 # note: tous les angles sont en radians
        beta=simplify_angle(beta)

        # Calcul de alpha
        tmp1=L2*sin(cte1)+L3*sin(beta)
        tmp2=L2*cos(cte1)+L3*cos(beta)
        tmp3=zbis/sqrt(tmp1**2+tmp2**2)
        cte2 = atan2(tmp2,tmp1)

        if (0<tmp3-1<0.0001):
            tmp3=1
        elif (-0.0001<tmp3+1<0):
            tmp3=-1

        if (rbis>0):
            alpha=-acos(tmp3)+cte2
        else:
            alpha=acos(tmp3)+cte2

        alpha=simplify_angle(alpha)


        # Calcul de gamma
        gamma=-(alpha+beta)*180/pi+angle

        gamma=gamma*pi/180
        gamma=simplify_angle(gamma)
    #     if(abs(alpha)<pi/2 and abs(beta)<pi/2 and abs(gamma)<pi/2):
    #         return [alpha, beta, gamma]
    #     else:
    #         print >>sys.stderr, "Non-accessible point: over-constrained angle"
    #         alpha = beta = gamma = 0
    #         return [alpha, beta, gamma]
    # else:
    #     print >>sys.stderr, "Non-accessible point: out of reach"
    #     alpha = beta = gamma = 0
    #     return [alpha, beta, gamma]


def coord3D_abg(x,y,z,angle=0):
    if(x==0 and y==0):
        theta=0
    else:
        theta=atan2(y,x)
    r=sqrt(pow(x,2)+pow(y,2))
    alpha,beta,gamma =coord2D_abg(r,z,angle)
    return (theta,alpha,beta,gamma)

def rad2mot(theta,alpha,beta,gamma): #les moteurs sont positionne inversement au modèle etablit et convertie en unite moteur
    mot1=round(((theta)*(180/pi)+180)/0.087890625)
    mot2=round(((-alpha)*(180/pi)+180)/0.087890625)
    mot3=round(((-beta)*(180/pi)+180)/0.087890625)
    mot4=round(((-gamma)*(180/pi)+180)/0.087890625)
    if(mot1<0 or mot1>4094 or mot2<760 or mot2>3200 or mot3<800 or mot3>3000 or mot4<1050 or mot4>3370):
        mot1 = mot2 = mot3 = mot4 = 2048
        print >>sys.stderr, "Non-accessible point"
    else:
        return (mot1,mot2,mot3,mot4)

# def draw_bras2D(alpha, beta, gamma, option=False):
#
#     '''Demande les positions angulaires des angles du bras (noté alpha, beta, gamma)
#     Retourne un schéma permettant de visualiser le bras entier (2D)
#     Le paramètre d'entrée "option" permet de tracer le bras sur une figure déjà existante '''
#
#     global L01, L2r, L2z, L3, L4,L5,L6
#     R=[-0.5,0.5,0,0]
#     Z=[0,0,0,7.5]
#
#
#
#     b2z=[-L2z*sin(alpha), L01+L2z*cos(alpha)]
#     b2=[b2z[0]+L2r*cos(alpha), b2z[1]+L2r*sin(alpha)]
#     b3=[b2[0]+L3*cos(alpha+beta), b2[1]+L3*sin(alpha+beta)]
#     b4=[b3[0]+L4*cos(alpha+beta+gamma), b3[1]+L4*sin(alpha+beta+gamma)]
#     b5=[b4[0]-L5*sin(alpha+beta+gamma),b4[1]+L5*cos(alpha+beta+gamma)]
#     b6=[b5[0]+L6*cos(alpha+beta+gamma-50*pi/180),b5[1]+L6*sin(alpha+beta+gamma-50*pi/180)]
#     R.append(b2z[0])
#     Z.append(b2z[1])
#     R.append(b2[0])
#     Z.append(b2[1])
#     R.append(b3[0])
#     Z.append(b3[1])
#     R.append(b4[0])
#     Z.append(b4[1])
#     R.append(b5[0])
#     Z.append(b5[1])
#     R.append(b6[0])
#     Z.append(b6[1])
#
#     if option==False:
#         plt.figure()
#         plt.axis('equal')
#
#
#     circle1=plt.Circle((0,7.5),0.5,color='r')
#     circle2=plt.Circle((b2[0],b2[1]),0.5,color='r')
#     circle3=plt.Circle((b3[0],b3[1]),0.5,color='r')
#     plt.plot(R,Z,'r-',linewidth=2,zorder = 2)
#
#     fig = plt.gcf()
#     ax = fig.gca()
#     ax.add_patch(circle1)
#     ax.add_patch(circle2)
#     ax.add_patch(circle3)
#
#     if option==False:
#         plt.title("Visualisation du bras avec commande en position ", fontsize=16)
#
#         plt.grid()
#         plt.xlabel('r(cm)')
#         plt.ylabel('z(cm)')
#         plt.show()

   ## script attraper palet au sol (le rendre generique)

xposcam=0
yposcam=-6.6
coord=[]
coord=sys.argv
L=len(coord)
if (L==4):
    xcam=float(coord[1])
    ycam=float(coord[2])
    z=-10 # a voir avec la base mobile
    x=xcam+xposcam
    y=yposcam+ycam
    angle=90
    obj_catch=int(coord[3])
elif (L==6):
   x=float(coord[1])
   y=float(coord[2])
   z=float(coord[3])
   angle=float(coord[4])
   obj_catch=int(coord[5])
else:
    print >>sys.stderr, 'error'
theta,alpha,beta,gamma= coord3D_abg(x,y,z,angle)
mot1,mot2,mot3,mot4=rad2mot(theta,alpha,beta,gamma)

print >>sys.stdout, str(mot1) + ' ' + str(mot2) + ' ' + str(mot3) + ' ' + str(mot4) + ' ' + str(obj_catch)

try:
    sys.stdout.close()
except:
    pass
try:
    sys.stderr.close()
except:
    pass
