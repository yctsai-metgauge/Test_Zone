#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <QSettings>
#include <QMessageBox>
#include <QElapsedTimer>
#include <math.h>

#include "new_tcp_thread.h"

#define Old_tibbo 0

//extern External_signal ext_signal;


unsigned long hex2dec(char *hex, int length)
{
    unsigned long result = 0;
    for (int i=0; i<length; i++)
    {
        result += (hex[i] & 0xff)*pow(16,length-i);
    }
    return result;
}

unsigned long laser_hex2dec(char *hex, int length)
{
    unsigned long result = 0;

    for (int i=0; i<length; i++) {
        result += ((hex[i] & 0xff) / 16 * 10 + (hex[i] & 0xff)%16) * pow(10, 2*(length-i-1));
    }
    return result;

}

new_tcp_thread::new_tcp_thread(QObject *parent) :
    QThread(parent),
    m_parse(new parse)
{
    PWMStruct = new PWM_Struct;
    lv1_signal = new External_signal;
    PWMStruct->pwm_manual = 0;
    PWMStruct->pwm_report_cnt = 0;
    PWMStruct->pwm_init_flag = 0;
    PWMStruct->pwm_stop = 0;
}

new_tcp_thread::~new_tcp_thread()
{
    delete m_parse;
    delete PWMStruct;
}

int new_tcp_thread::Connect(QString IP_address,int Port)
{
    qDebug()<<"new_tcp_thread::Connect func is called";

    tcpClient = new QTcpSocket;
    qDebug() <<"IP:" << IP_address <<" Port:"<< Port <<"with " << QThread::currentThreadId()<<"\n";
    tcpClient->socketOption(QAbstractSocket::LowDelayOption	);
    tcpClient->setSocketOption(QAbstractSocket::LowDelayOption,1);
    if (IP_address == Master_IP_Address) {
        if (Port == 1001)
            connect(tcpClient,SIGNAL(readyRead()),this,SLOT(Cmd_onSocketReadyRead()));
        else if (Port == 1002)
            connect(tcpClient,SIGNAL(readyRead()),this,SLOT(Laser1_SocketRead()));
        else
            connect(tcpClient,SIGNAL(readyRead()),this,SLOT(Tempe_onSocketReadyRead()));
    }
    else if (IP_address == Slave_IP_Address) {
        if (Port == 1002)
            connect(tcpClient,SIGNAL(readyRead()),this,SLOT(Laser2_SocketRead()));
        else
            connect(tcpClient,SIGNAL(readyRead()),this,SLOT(Pyrometer_onSocketReadyRead()));
    }
    else if (IP_address == CBox_IP_Address) {
        if (Port == 1001)
            connect(tcpClient,SIGNAL(readyRead()),this,SLOT(CBox_Cmd_onSocketReadyRead()));
        else if (Port == 1002)
            connect(tcpClient,SIGNAL(readyRead()),this,SLOT(CBox_Switch_onSocketReadyRead()));
        else
            connect(tcpClient,SIGNAL(readyRead()),this,SLOT(CBox_Maf_and_Speed_onSocketReadyRead()));
    }
    else if (IP_address == WireMaster) {
        if (Port == 1001)
            connect(tcpClient,SIGNAL(readyRead()),this,SLOT(Cmd_onSocketReadyRead()));

        else if (Port == 1002){
            qDebug() <<"COnnect Here" <<"\n";
            connect(tcpClient,SIGNAL(readyRead()),this,SLOT(Laser_onSocketReadyRead_Wire()));
        }
        else
            connect(tcpClient,SIGNAL(readyRead()),this,SLOT(Tempe_onSocketReadyRead()));
    }
    else if (IP_address == CGMaster) {
        if (Port == 1001)
            connect(tcpClient,SIGNAL(readyRead()),this,SLOT(Cmd_onSocketReadyRead()));
        else
            connect(tcpClient,SIGNAL(readyRead()),this,SLOT(Tempe_onSocketReadyRead()));
    }
    else if (IP_address == CGTibbo) {
        if (Port == 1001)
            connect(tcpClient,SIGNAL(readyRead()),this,SLOT(CBox_Cmd_onSocketReadyRead()));
        else if (Port == 1002)
            connect(tcpClient,SIGNAL(readyRead()),this,SLOT(CBox_Switch_onSocketReadyRead()));
        else
            connect(tcpClient,SIGNAL(readyRead()),this,SLOT(CBox_Maf_and_Speed_onSocketReadyRead()));
    }


    connect(tcpClient,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this,SLOT(onSocketStateChange(QAbstractSocket::SocketState)));

    connect(tcpClient,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(tcpClient,SIGNAL(disconnected()),this,SLOT(onDisconnected()));

    if (tcpClient->state()==QAbstractSocket::ConnectedState)
        tcpClient->disconnectFromHost();

    while (!quit)
    {
        const int Timeout = 3 *1000;
        tcpClient->connectToHost(IP_address,Port);
        quit = tcpClient->waitForConnected(Timeout);
        if (!quit) {
            emit error(tcpClient->error(),tcpClient->errorString());
            return 0;
        }
    }
    return 1;
}

void new_tcp_thread::Disconnect()
{
    if (tcpClient->state()==QAbstractSocket::ConnectedState) {
        tcpClient->disconnectFromHost();
        quit = false;
    }
}

void new_tcp_thread::onConnected()
{
    qDebug() << tcpClient->peerName() << tcpClient->peerPort() << "NEW connect";
    emit tcp_thread_connect(tcpClient->peerName(),tcpClient->peerPort());
}

void new_tcp_thread::onDisconnected()
{
    quit = false;
    emit tcp_thread_disconnect(tcpClient->peerName(),tcpClient->peerPort());
}

void new_tcp_thread::onSocketStateChange(QAbstractSocket::SocketState socketState)
{
    switch(socketState)
    {
        case QAbstractSocket::UnconnectedState:
            state = UnconnectedState;
            break;
        case QAbstractSocket::HostLookupState:
            state = HostLookupState;
            break;
        case QAbstractSocket::ConnectingState:
            state = ConnectingState;
            break;
        case QAbstractSocket::ConnectedState:
            state = ConnectedState;
            break;
        case QAbstractSocket::BoundState:
            state = BoundState;
            break;
        case QAbstractSocket::ClosingState:
            state = ClosingState;
            break;
        case QAbstractSocket::ListeningState:
            state = ListeningState;
            break;
    }
}

void new_tcp_thread::write(const char *data)
{
    if (tcpClient->state()==QAbstractSocket::ConnectedState)
        tcpClient->write(data);
}

int new_tcp_thread::isOpen()
{
    return tcpClient->isOpen();
}

void new_tcp_thread::getTibboFlag(bool flag)
{
    if (flag)
        newTibbo = true;
    else
        newTibbo = false;
}

void new_tcp_thread::getTHSensor(int s)
{
    THSensors = s;
}

// Tibbo 1 port 1001
void new_tcp_thread::Cmd_onSocketReadyRead()
{
    /// Leave for future
}

// Tibbo 1 port 1002
void new_tcp_thread::Laser1_SocketRead()
{
    qDebug()<<"Laser1_SocketRead func is called";

    QByteArray data = tcpClient->readAll();
    int len = data.length();

    for (int i = 0; i < len; i = i + 29) {
        if (i != 0)
            data = data.mid(29);

        char *RecvData = data.data();
        gauge.Buffer = RecvData;

        int result = m_parse->Metgauge_GaugeVerifyChecksum(RecvData, LASER_DIAMETER_NUM_3);
        if (result!=1)
            return;

        if (AxisNum == 2 || AxisNum == 4) {
            if (newTibbo) {
                diameter[0] = diameterReadOut(&gauge.Buffer[4], 4);
                diameter[1] = diameterReadOut(&gauge.Buffer[12], 4);

                offset[0] = diameterReadOut(&gauge.Buffer[8], 4);
                offset[1] = diameterReadOut(&gauge.Buffer[16], 4);
            }
            else {
            diameter[0] = diameterReadOut(&gauge.Buffer[5], 3);
            diameter[1] = diameterReadOut(&gauge.Buffer[13], 3);

            offset[0] = diameterReadOut(&gauge.Buffer[9], 3);
            offset[1] = diameterReadOut(&gauge.Buffer[17], 3);
        }
        }
        else {
            if (newTibbo) {
                diameter[0] = diameterReadOut(&gauge.Buffer[4], 4);
                diameter[1] = diameterReadOut(&gauge.Buffer[12], 4);
                diameter[2] = diameterReadOut(&gauge.Buffer[20], 4);

                offset[0] = diameterReadOut(&gauge.Buffer[8], 4);
                offset[1] = diameterReadOut(&gauge.Buffer[16], 4);
                offset[2] = diameterReadOut(&gauge.Buffer[24], 4);
            }
        else {
            diameter[0] = diameterReadOut(&gauge.Buffer[5], 3);
            diameter[1] = diameterReadOut(&gauge.Buffer[13], 3);
            diameter[2] = diameterReadOut(&gauge.Buffer[21], 3);

            offset[0] = diameterReadOut(&gauge.Buffer[9], 3);
            offset[1] = diameterReadOut(&gauge.Buffer[17], 3);
            offset[2] = diameterReadOut(&gauge.Buffer[25], 3);
        }

        }
        switch (AxisNum)
        {
        case 2:
            emit sendBackXYDiameter(diameter);
            emit sendBackOffet(offset);
            break;
        case 3:
            emit sendBackXYZDiameter(diameter);
            emit sendBackOffet(offset);
            break;
        case 4:
            emit sendXYDiameter(diameter);
            emit sendOffet(offset);
            break;
        case 5:
        case 6:
            emit sendXYZDiameter(diameter);
            emit sendOffet(offset);
            break;
        }
    }
}

// Tibbo 1 port 1003
void new_tcp_thread::Tempe_onSocketReadyRead()
{
    qDebug()<<"Tempe_onSocketReadyRead func is called";

    Temperature_Pkt TempePkt;
    QByteArray data = tcpClient->readAll();
    char *RecvData = data.data();
    TempePkt.Buffer = RecvData;

    int len = data.length();

    int len_tempe_thr = 0;
    int len_PWM_thr = 0;
    switch (ATON) {
    case ROD:
    case ROD_40:
        len_tempe_thr = RECV_TEMP_ROD;
        len_PWM_thr = RECV_PWM_ROD;
        break;
    case BAR:
        len_tempe_thr = RECV_TEMP_BAR;
        len_PWM_thr = RECV_PWM_BAR;
        break;
    case WIRE:
        len_tempe_thr = RECV_TEMP_WIRE;
        len_PWM_thr = RECV_PWM_WIRE;
        break;
    case CG:
        len_tempe_thr = RECV_TEMP_CG;
        len_PWM_thr = RECV_PWM_CG;
        break;
    default:
        break;
    }


    // len 41, 7, 9, 10
    if (len >= len_tempe_thr) {
        int temp_check_result = m_parse->Metgauge_TempVerifyChecksum(RecvData, len_tempe_thr);
        if (ATON == WIRE)
            temp_check_result = 1;
        if (temp_check_result == 1) {
            // Calculate temperature/ humidity values
            switch (ATON) {
            case ROD:
            case ROD_40:
            case CG:
            case BAR:
                TempeReadOut(RecvData);
                break;
            case WIRE:
                TempeReadOut_Wire(&TempePkt);
                break;
            default:
                break;
            }

            emit sendBackTempValue(temperature, humidity);
        }
    }
    else if (len == len_PWM_thr) { // Tibbo version 21-05 PWM length 17
        TempePkt.Pkt.PwmPkt.index = hex2dec(&TempePkt.Buffer[0],4);
        switch (ATON) {
        case ROD:
        case ROD_40:
        case WIRE:
        case CG:
            PWMStruct->pwm_value     = (((RecvData[4]& 0xff) << 8) + (RecvData[5]& 0xff));
            PWMStruct->pwm_current   = (((RecvData[6]& 0xff) << 8)  + (RecvData[7]& 0xff)) * 0.01;
            break;
        case BAR:
            PWMStruct->pwm_value     = (((RecvData[4]& 0xff)  << 8) + (RecvData[4]& 0xff));
            PWMStruct->pwm_current   = (((RecvData[6]& 0xff)  << 8) + (RecvData[6]& 0xff)) * 0.01;
            PWMStruct->pwm_value_1   = (((RecvData[8]& 0xff)  << 8) + (RecvData[8]& 0xff));
            PWMStruct->pwm_current_1 = (((RecvData[10]& 0xff) << 8) + (RecvData[10]& 0xff)) * 0.01;
            break;
        default:
            break;
        }
        PWMStruct->pwm_report_cnt++;

        if (PWMStruct->pwm_manual == 1 && PWMStruct->pwm_current == 0.0 && PWMStruct->pwm_report_cnt > 10) {
            PWMStruct->pwm_manual = 0;
            PWMStruct->pwm_stop = 1;
            PWMStruct->pwm_init_flag = 1;
        }
        emit sendBackPWM(PWMStruct);
    }
    else if (len == RECV_AIRFLOW) {
        switch (ATON) {
        case WIRE:
            flow_value = (((RecvData[4]& 0xff) << 8) +  (RecvData[5]& 0xff)) / 100.0;
            emit sendBackAirFlow(flow_value);
            break;
        default:
            break;
        }
    }
}

// Tibbo 2 port 1002
void new_tcp_thread::Laser2_SocketRead()
{
    qDebug()<<"Laser2_SocketRead func is called";
    QByteArray data = tcpClient->readAll();
    int len = data.length();

    for (int i = 0; i < len; i = i + 29) {
        if (i != 0)
            data = data.mid(29);

        char *RecvData = data.data();
        gauge.Buffer = RecvData;

        int result = m_parse->Metgauge_GaugeVerifyChecksum(RecvData, LASER_DIAMETER_NUM_3);
        if (result!=1)
            return;

        if (newTibbo) {
            if (AxisNum == 4) {
                diameter[2] = diameterReadOut(&gauge.Buffer[4], 4);
                diameter[3] = diameterReadOut(&gauge.Buffer[12], 4);

                offset[2] = diameterReadOut(&gauge.Buffer[8], 4);
                offset[3] = diameterReadOut(&gauge.Buffer[16], 4);
            }
            else if (AxisNum == 5) {
                diameter[3] = diameterReadOut(&gauge.Buffer[4], 4);
                diameter[4] = diameterReadOut(&gauge.Buffer[12], 4);

                offset[3] = diameterReadOut(&gauge.Buffer[8], 4);
                offset[4] = diameterReadOut(&gauge.Buffer[16], 4);
            }
            else if (AxisNum == 6) {
                diameter[3] = diameterReadOut(&gauge.Buffer[4], 4);
                diameter[4] = diameterReadOut(&gauge.Buffer[12], 4);
                diameter[5] = diameterReadOut(&gauge.Buffer[20], 4);

                offset[3] = diameterReadOut(&gauge.Buffer[8], 4);
                offset[4] = diameterReadOut(&gauge.Buffer[16], 4);
                offset[5] = diameterReadOut(&gauge.Buffer[24], 4);
            }
        }
        else {
            if (AxisNum == 4) {
                diameter[2] = diameterReadOut(&gauge.Buffer[5], 3);
                diameter[3] = diameterReadOut(&gauge.Buffer[13], 3);

                offset[2] = diameterReadOut(&gauge.Buffer[9], 3);
                offset[3] = diameterReadOut(&gauge.Buffer[17], 3);
            }
            else if (AxisNum == 5) {
                diameter[3] = diameterReadOut(&gauge.Buffer[5], 3);
                diameter[4] = diameterReadOut(&gauge.Buffer[13], 3);

                offset[3] = diameterReadOut(&gauge.Buffer[9], 3);
                offset[4] = diameterReadOut(&gauge.Buffer[17], 3);
            }
            else if (AxisNum == 6) {
                diameter[3] = diameterReadOut(&gauge.Buffer[5], 3);
                diameter[4] = diameterReadOut(&gauge.Buffer[13], 3);
                diameter[5] = diameterReadOut(&gauge.Buffer[21], 3);

                offset[3] = diameterReadOut(&gauge.Buffer[9], 3);
                offset[4] = diameterReadOut(&gauge.Buffer[17], 3);
                offset[5] = diameterReadOut(&gauge.Buffer[25], 3);
            }
        }

        switch (AxisNum)
        {
        case 4:
            diameter[0] = Axis_X_signal;
            diameter[1] = Axis_Y_signal;

            emit sendBackDiameter(diameter);
            emit sendBackOffet(offset);

            break;
        case 5:
            diameter[0] = Axis_X_signal;
            diameter[1] = Axis_Y_signal;
            diameter[2] = Axis_Z_signal;

            emit sendBackDiameter(diameter);
            emit sendBackOffet(offset);
            break;
        case 6:
            diameter[0] = Axis_X_signal;
            diameter[1] = Axis_Y_signal;
            diameter[2] = Axis_Z_signal;

            emit sendBackDiameter(diameter);
            emit sendBackOffet(offset);
            break;
        }
    }
    return;
}

void new_tcp_thread::Laser_onSocketReadyRead_Wire()
{
    qDebug()<<"Laser_onSocketReadyRead_Wire func is called";
    float dia[2];
    QByteArray data = tcpClient->readAll();
    int len = data.length();
    if (len > 100)
        return;

    if (newTibbo) {
        for (int i = 0; i < len; i = i + 29) {
            if (i != 0)
                data = data.mid(29);

            char *RecvData = data.data();
            gauge.Buffer = RecvData;

            int result = m_parse->Metgauge_GaugeVerifyChecksum(RecvData, LASER_DIAMETER_NUM_3);
            if (result!=1)
                return;

            dia[0] = hex2decNew(&gauge.Buffer[4],4);
            dia[1] = hex2decNew(&gauge.Buffer[12],4);
            emit sendBackXYDiameter(dia);
        }
    }
    else {
        for (int i = 0; i < len; i = i + 13) {
            if (i != 0)
                data = data.mid(13);
            char *RecvData = data.data();
            gauge.Buffer = RecvData;
            dia[0] = laser_hex2dec(&gauge.Buffer[5],3)/1000.0;
            dia[1] = laser_hex2dec(&gauge.Buffer[9],3)/1000.0;
            emit sendBackXYDiameter(dia);
        }
    }

}

// Tibbo 2 port 1003
void new_tcp_thread::Pyrometer_onSocketReadyRead()
{
    QByteArray data = tcpClient->readAll();
    char *RecvData = data.data();
    int len = data.length();

    if (len >= 9) {
        int check_result = m_parse->Metgauge_TempVerifyChecksum(RecvData,9);
        if (check_result == 1) {
            pyrometer_value = ((RecvData[6]& 0x7f) << 8) + ((RecvData[7]& 0x7f));
            emit sendBackPyro(pyrometer_value);
            emit sendPyrometer(pyrometer_value);
        }
    }
}

// Tibbo 3 port 1001
void new_tcp_thread::CBox_Cmd_onSocketReadyRead()
{
        /// Leave for future
}

// Tibbo 3 port 1002
void new_tcp_thread::CBox_Switch_onSocketReadyRead()
{
    QByteArray data = tcpClient->readAll();
    char *RecvData = data.data();
    int event_check_result = m_parse->Metgauge_GaugeVerifyChecksum(RecvData,45);

    // Little Endian
    if (event_check_result) {
        Temperature_Pkt TempePkt;
        TempePkt.Buffer = RecvData;
        TempePkt.Pkt.EventPkt.DeviceID = TempePkt.Buffer[3]*4096 + TempePkt.Buffer[2]*256 + TempePkt.Buffer[1]*16 + TempePkt.Buffer[0];

        TempePkt.Pkt.EventPkt.ErrCode = TempePkt.Buffer[7]*4096 + TempePkt.Buffer[6]*256 + TempePkt.Buffer[5]*16 + TempePkt.Buffer[4];

        // To be defined error code  1: Signal for start 0: Signal for stop
        if ( TempePkt.Pkt.EventPkt.ErrCode == 1)
            emit sendRunningSignal(true);
        else
            emit sendRunningSignal(false);
    }
}

// Tibbo 3 port 1003
void new_tcp_thread::CBox_Maf_and_Speed_onSocketReadyRead()
{
    QByteArray data = tcpClient->readAll();
    char *RecvData = data.data();
    int len = data.length();

    if (len == 29) {
        for (int i = 4; i < len; i = i + 4) {
            switch(i)
            {
            case 4:
                //ext_signal.SpeedType = RecvData[i];
                //mySettings.setValue("SpeedType",ext_signal.SpeedType);
                break;
            case 8:
                //ext_signal.SpeedActive = RecvData[i];
                //mySettings.setValue("SpeedActive",ext_signal.SpeedActive);
                break;
            case 12:
                //ext_signal.SwitchType = RecvData[i];
                //mySettings.setValue("SwitchType",ext_signal.SwitchType);
                break;
            case 16:
                //ext_signal.Ch1Type = RecvData[i];
                //mySettings.setValue("Ch1Type",ext_signal.Ch1Type);
                break;
            case 20:
                //ext_signal.Ch2Type = RecvData[i];
                //mySettings.setValue("Ch2Type",ext_signal.Ch2Type);
                break;
            case 24:
                //ext_signal.SwitchActive = RecvData[i];
                //mySettings.setValue("SwitchActive",ext_signal.SwitchActive);
                break;
            }
        }
    }
    else if (len == 41) {
        int temp_check_result = m_parse->Metgauge_TempVerifyChecksum(RecvData,41);
        if (temp_check_result==1) {
            CBox_temperature[0] = (((RecvData[4]&0xff)  << 8 ) + (RecvData[5]&0xff)) /10.0;
            CBox_temperature[1] = (((RecvData[6]&0xff)  << 8 ) + (RecvData[7]&0xff)) /10.0;
            CBox_humidity[0]    = (((RecvData[22]&0xff) << 8 ) + (RecvData[23]&0xff))/10.0;
            CBox_humidity[1]    = (((RecvData[24]&0xff) << 8 ) + (RecvData[25]&0xff))/10.0;


            emit sendBackCboxTemp(CBox_temperature, CBox_humidity);
        }
    }
    // flow_value, 7 bytes  Little Endian
    else if (len == RECV_AIRFLOW) {
        flow_value = (((RecvData[4]& 0xff) << 8) +  (RecvData[5]& 0xff)) / 100.0;
        emit sendBackAirFlow(flow_value);
    }

    //Speed Analog 10 bytes, Little Endian
    else if (len == RECV_SPEED_ANALOG) {
        float fTemp;
        char fByte[] = {data[5], data[6], data[7], data[8]};
        memcpy(&fTemp, &fByte, sizeof(fTemp));
        speed_analog = fTemp * lv1_signal->VoltageToSpeed;
        emit sendBackSpeed(speed_analog);
    }

    //Speed Digital 9 bytes, Little Endian
    else if (len == RECV_SPEED_DIGITAL) {
        quint16 sTemp;
        char sByte[] = {data[5], data[6]};
        memcpy(&sTemp, &sByte, sizeof(quint16));
        sTemp *= 5;
        speed_digital = sTemp / lv1_signal->CountToSpeed;
        emit sendBackSpeed(speed_digital);
    }
    // Switch
    else if (len == 45) {
        // Little Endian
            Temperature_Pkt TempePkt;
            TempePkt.Buffer = RecvData;
            TempePkt.Pkt.EventPkt.DeviceID = TempePkt.Buffer[3]*4096 + TempePkt.Buffer[2]*256 + TempePkt.Buffer[1]*16 + TempePkt.Buffer[0];
            TempePkt.Pkt.EventPkt.ErrCode = TempePkt.Buffer[7]*4096 + TempePkt.Buffer[6]*256 + TempePkt.Buffer[5]*16 + TempePkt.Buffer[4];

            // To be defined error code  1: Signal for start 0: Signal for stop
            if ( TempePkt.Pkt.EventPkt.ErrCode == 1)
                emit sendRunningSignal(true);
            else
                emit sendRunningSignal(false);
    }

}

// Big endian
float new_tcp_thread::diameterReadOut(char *hex, int )
{
    float fresult = 0.0;
    unsigned long result = 0;

    if (newTibbo)
        result += (hex[0] & 0xff) + ((hex[1] & 0xff) << 8) + ((hex[2] & 0xff) << 16) + ((hex[3] & 0xff) << 24);
    else
        result += ((hex[0] & 0xff) << 16) + ((hex[1] & 0xff) << 8) + (hex[2] & 0xff);

    fresult = result / 1000.0;
    return fresult;
}

float new_tcp_thread::diameterReadOutD(char *hex, int)
{
    float fresult = 0.0;
    unsigned long result = 0;

    if (newTibbo)
        result += (hex[0] & 0xff) + ((hex[1] & 0xff) << 8) + ((hex[2] & 0xff) << 16) + ((hex[3] & 0xff) << 24);
    else
        result += ((hex[0] & 0xff) << 16) + ((hex[1] & 0xff) << 8) + (hex[2] & 0xff);

    qDebug() << result;
    fresult = result / 1000.0;
    return fresult;
}

// Temperature calculation
void new_tcp_thread::TempeReadOut(char* hex)
{
    double dTemp = 0.0;
    double dHumid = 0.0;
    // Shift 1 bytes
    for (int i =0; i < THSensors; i++) {
        if (THSensors == 12) {
            dTemp =  (((hex[4  + i*2]&0xff) << 8 ) + (hex[5  + i*2]&0xff));
            dHumid = (((hex[28 + i*2]&0xff) << 8 ) + (hex[29 + i*2]&0xff));
        }
        else if (THSensors <= 9) {
            dTemp =  (((hex[4  + i*2]&0xff) << 8 ) + (hex[5  + i*2]&0xff));
            dHumid = (((hex[22 + i*2]&0xff) << 8 ) + (hex[23 + i*2]&0xff));
        }
        else if (THSensors == 14) {
            dTemp =  (((hex[4  + i*2]&0xff) << 8 ) + (hex[5  + i*2]&0xff));
            dHumid = (((hex[32 + i*2]&0xff) << 8 ) + (hex[33 + i*2]&0xff));
        }
        temperature[i]  = dTemp/10;
        humidity[i] = dHumid/10;
    }
}

void new_tcp_thread::TempeReadOut_Wire(Temperature_Pkt *TempePkt)
{
    double dTemp = 0.0;
    double dHumid = 0.0;
    for (int i =0; i < TEMP_SENSOR_NUM_ROD; i++) { // Need 9: 5 sensor, 2 empty, CBox, Blower
        dTemp =  (((TempePkt->Buffer[4  + i*2]&0xff) << 8) + (TempePkt->Buffer[5  + i*2]&0xff));
        dHumid = (((TempePkt->Buffer[22 + i*2]&0xff) << 8) + (TempePkt->Buffer[23 + i*2]&0xff));
        temperature[i]  = dTemp/10;
        humidity[i] = dHumid/10;
    }
}

// Tibbo 2
// - Sync with Tibbo 1
void new_tcp_thread::getXYZDiameter(float *XYZ)
{
    if (AxisNum == 4) {
        Axis_X_signal = XYZ[0];
        Axis_Y_signal = XYZ[1];
    }
    else {
        Axis_X_signal = XYZ[0];
        Axis_Y_signal = XYZ[1];
        Axis_Z_signal = XYZ[2];
    }
}

void new_tcp_thread::getOffset(float *off)
{
    if (AxisNum == 4) {
        offset[0] = off[0];
        offset[1] = off[1];
    }
    else {
        offset[0] = off[0];
        offset[1] = off[1];
        offset[2] = off[2];
    }
}

// - Sync with Tibbo 3
void new_tcp_thread::getPyrometer(qreal pyro)
{
    if (pyro <= 1)
        pyrometer_value = 0;
    else
        pyrometer_value = pyro;
}

// Tibbo 3
void new_tcp_thread::getUnit(UNIT_Type unit)
{
    unitType = unit;
}

void new_tcp_thread::getPWMValue(PWM_Struct *PWM)
{
    memcpy(PWMStruct, PWM, sizeof(PWM_Struct));
}

void new_tcp_thread::getExtSignalConfig(External_signal *inputConfig)
{
    memcpy(lv1_signal, inputConfig, sizeof(External_signal));
}

void new_tcp_thread::getResetExtSignal(External_signal *inputConfig)
{
    int boolCount = 6;
    char Pkt[19]= {'%','E','W',
                         '0','1','0','1','0','1',
                         '0','1','0','1','0','1',
                         '0','6',
                   '&',0x0D};
    if (!inputConfig->SpeedType) {
        Pkt[4] = '0';
        boolCount--;
    }
    if (!inputConfig->SpeedActive) {
        Pkt[6] = '0';
        boolCount--;
    }
    if (!inputConfig->SwitchType)  {
        Pkt[8] = '0';
        boolCount--;
    }
    if (!inputConfig->Ch1Type)  {
        Pkt[10] = '0';
        boolCount--;
    }
    if (!inputConfig->Ch2Type)  {
        Pkt[12] = '0';
        boolCount--;
    }
    if (!inputConfig->SwitchActive)  {
        Pkt[14] = '0';
        boolCount--;
    }
    Pkt[16] = static_cast<char>(boolCount) + '0';
    write(Pkt);
}

// LV1  signal
void new_tcp_thread::getLV1Signal(bool signal1, bool signal2, bool signal3, bool signal4)
{
    // Tibbo connection for LV1
    if (signal1) {
        const char Pkt[11]= {'%','S','S','R','1','0','0','0','1','&',0x0D};
        write(Pkt);
    }
    else {
        const char Pkt[11]= {'%','S','S','R','1','0','0','0','0','&',0x0D};
        write(Pkt);
    }
    wait(5);
    if (signal2) {
        const char Pkt[11]= {'%','S','S','R','2','0','0','0','1','&',0x0D};
        write(Pkt);
    }
    else {
        const char Pkt[11]= {'%','S','S','R','2','0','0','0','0','&',0x0D};
        write(Pkt);
    }
    wait(5);
    if (signal3) {
        const char Pkt[11]= {'%','S','S','R','3','0','0','0','1','&',0x0D};
        write(Pkt);
    }
    else {
        const char Pkt[11]= {'%','S','S','R','3','0','0','0','0','&',0x0D};
        write(Pkt);
    }
    wait(5);
    if (signal4) {
        const char Pkt[11]= {'%','S','S','R','4','0','0','0','1','&',0x0D};
        write(Pkt);
    }
    else {
        const char Pkt[11]= {'%','S','S','R','4','0','0','0','0','&',0x0D};
        write(Pkt);
    }
}

void new_tcp_thread::getLV1S1(bool sign)
{
    // Tibbo connection for LV1
    if (sign) {
        const char Pkt[11]= {'%','S','S','R','1','0','0','0','1','&',0x0D};
        write(Pkt);
    }
    else {
        const char Pkt[11]= {'%','S','S','R','1','0','0','0','0','&',0x0D};
        write(Pkt);
    }
}

void new_tcp_thread::getLV1S2(bool sign)
{
    // Tibbo connection for LV1
    if (sign) {
        const char Pkt[11]= {'%','S','S','R','2','0','0','0','1','&',0x0D};
        write(Pkt);
    }
    else {
        const char Pkt[11]= {'%','S','S','R','2','0','0','0','0','&',0x0D};
        write(Pkt);
    }
}

void new_tcp_thread::getLV1S3(bool sign)
{
    // Tibbo connection for LV1
    if (sign) {
        const char Pkt[11]= {'%','S','S','R','3','0','0','0','1','&',0x0D};
        write(Pkt);
    }
    else {
        const char Pkt[11]= {'%','S','S','R','3','0','0','0','0','&',0x0D};
        write(Pkt);
    }
}

void new_tcp_thread::getLV1S4(bool sign)
{
    // Tibbo connection for LV1
    if (sign) {
        const char Pkt[11]= {'%','S','S','R','4','0','0','0','1','&',0x0D};
        write(Pkt);
    }
    else {
        const char Pkt[11]= {'%','S','S','R','4','0','0','0','0','&',0x0D};
        write(Pkt);
    }
}

//Big Endian
uint new_tcp_thread::charToUint(char *inputC)
{
    uint64_t size = sizeof(uint);
    for (unsigned long long i = 0; i < size; i++)
    {
        u.uByte[(size - 1) - i] = inputC[i];
    }
    return u.uTemp;
}

//Little Endian
uint new_tcp_thread::charToUintL(char *inputC)
{
    uint64_t size = sizeof(uint);
    for (unsigned long long i = 0; i < size; i++)
    {
        u.uByte[i] = inputC[i];
    }
    return u.uTemp;
}

// New Tibbo calculation
float new_tcp_thread::hex2decNew(char *hex, int length)
{
    float fresult = 0.0;
    unsigned long result = 0;
    unsigned long tmp = 0;

    for (int i=0; i<length; i++) {
        switch (i)
        {
        case 0:
            tmp = (hex[i] & 0xff);
            break;
        case 1:
            tmp = (hex[i] & 0xff) << 8;
            break;
        case 2:
            tmp = (hex[i] & 0xff) << 16;
            break;
        default:
            tmp = (hex[i] & 0xff) << 24;
            break;
        }
        result += tmp;
    }
    fresult = result / 1000.0;
    return fresult;
}
