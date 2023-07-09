#ifndef TEMPCONVERTER_H
#define TEMPCONVERTER_H

#include <QObject>

class TempConverter : public QObject
{
    Q_OBJECT

private:
    int tempC;

public:
    explicit TempConverter(int tempc, QObject *parent = nullptr);
    int getTempC();
    int getTempF();
public slots:
    void setTempC(int i);
    void setTempF(int i);

signals:
    void tempCChanged(int i);
    void tempFChanged(int i);

};

#endif // TEMPCONVERTER_H
