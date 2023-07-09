#include "tempconverter.h"

TempConverter::TempConverter(int tempc, QObject *parent)
    :  QObject{parent} , tempC(tempc)
{

}


int TempConverter::getTempC()
{
    return tempC;
}

int TempConverter::getTempF()
{
    int f = round((9.0 / 5.0) * tempC + 32);
    return f;

}

void TempConverter::setTempC(int i)
{
    if(tempC == i)
    {
        return;
    }

    tempC = i;
    emit tempCChanged(tempC);
    emit tempFChanged(getTempF());
}

void TempConverter::setTempF(int f)
{
    int c =round((5.0 / 9.0) * (f - 32));
    setTempC(c);
}
