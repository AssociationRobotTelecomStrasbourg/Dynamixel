#include "XM_bulk_chain.h"
#include "XM430-W210_Control_Table.h"

int main(int argc,char** argv)
{
    createControlTable();
    XM_bulk_chain* Chain;
    Chain = new XM_bulk_chain(5,1000000);
    uint8_t baudrate = 1;
    for(int id=1;id<6;id++)
    {
        Chain->setParam(id,"Baud Rate",baudrate);
    }
    Chain->write();
    delete Chain;
    Chain = new XM_bulk_chain(5);
    return 0;
}
