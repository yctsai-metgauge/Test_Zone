#ifndef _NEW_TCP_Thread
#define _NEW_TCP_Thread

#include <QThread>
#include <QTimer>
#include <QTcpSocket>
#include <QIODevice>
#include <QFile>

#include "Logger.h"
#include "rodcheck.h"
#include "parse.h"

#define RECV_TEMP_WIRE 41
#define RECV_TEMP_ROD 41
#define RECV_TEMP_BAR 53
#define RECV_PWM_WIRE 9
#define RECV_PWM_ROD 9
#define RECV_PWM_BAR 13
#define RECV_TEMP_CG 61
#define RECV_PWM_CG 9

#define RECV_TEMP           (53) // 9sensors:41 , 12sensors:53
#define RECV_PWM            (13)  //9->13
#define RECV_AIRFLOW        (7)
#define RECV_SPEED_DIGITAL  (8)
#define RECV_SPEED_ANALOG   (10)
#define RECV_EVENT          (45)

#define LASER_DIAMETER_NUM_1 (13)
#define LASER_DIAMETER_NUM_2 (21)
#define LASER_DIAMETER_NUM_3 (29)

#define ECHO_SPEED_DIGITAL  (0xE2)
#define ECHO_SPEED_ANALOG   (0xE3)

typedef unsigned int   uint32;

typedef struct
{
        uint32 Head;
        float Laser_Diameter_1;
        float Laser_Offset_1;
        float Laser_Diameter_2;
        float Laser_Offset_2;
        float Laser_Diameter_3;
        float Laser_Offset_3;
}Master_Sensor_Pkt;

typedef struct
{
        uint32 Head;
        float Laser_Diameter_4;
        float Laser_Offset_4;
        float Laser_Diameter_5;
        float Laser_Offset_5;
        float Laser_Diameter_6;
        float Laser_Offset_6;
}Slave_Sensor_Pkt;

typedef struct
{
    char *Buffer;
    union
    {
        Master_Sensor_Pkt Mpkt;
        Slave_Sensor_Pkt  Spkt;
    }Pkt;
}Gauge_Sensor_Pkt;

typedef struct
{
        uint32 index;
        float T[TEMP_SENSOR_NUM];
        float H[TEMP_SENSOR_NUM];
}Master_Temperature_Pkt;

typedef struct
{
        uint32 index;
        float value;
}Pyrometer_Pkt;

typedef struct
{
        uint32 index;
}Pwm_Pkt;

typedef struct
{
    uint32 DeviceID;
    uint32	ErrCode;
    tm Time;
}Event_Pkt;

typedef struct
{
    char *Buffer;
    union
    {
        Master_Temperature_Pkt Tpkt;
        Pyrometer_Pkt Ppkt;
        Pwm_Pkt PwmPkt;
        Event_Pkt EventPkt;
    }Pkt;
}Temperature_Pkt;

class new_tcp_thread : public QThread
{
    Q_OBJECT
public:
    explicit new_tcp_thread(QObject *parent = 0);// : QThread(parent)
    ~new_tcp_thread();
    int Connect(QString IP_address,int Port);
    void Disconnect();
    void write(const char *data);
    int isOpen();
    int  state;
    unsigned int AxisNum;
    ATON_TYPE ATON;
//    Presets_Struct *PresetTcpThread;
    QTcpSocket  *tcpClient = nullptr;  //socket
    QString WireMaster = "192.168.50.88";
    QString CGMaster = "192.168.50.112";
    QString CGTibbo = "192.168.50.113";


    QString TDSIP = "192.168.50.73";

private:
    parse *m_parse = nullptr;
    bool quit = 0;
    bool newTibbo = false;
    void TempeReadOut(char*);
    void TempeReadOut_Wire(Temperature_Pkt*);

    uint charToUint(char*);
    uint charToUintL(char*);
    float diameterReadOut(char *hex, int length);
    float diameterReadOutD(char *hex, int length);

    Gauge_Sensor_Pkt gauge;
    //int if_dimension_calibration;
    double temperature[TEMP_SENSOR_NUM] = {0};
    double humidity[TEMP_SENSOR_NUM] = {0};

    double CBox_temperature[TEMP_SENSOR_NUM]={0};
    double CBox_humidity[TEMP_SENSOR_NUM]={0};
    qreal flow_value;
    float speed_digital, speed_analog;
    qreal pyrometer_value = 0.0;
    PWM_Struct *PWMStruct;
    External_signal *lv1_signal;
    float diameter[MAXIMUM_AXIS_NUM];
    float offset[MAXIMUM_AXIS_NUM];

    float Axis_X_signal;
    float Axis_Y_signal;
    float Axis_Z_signal;

    UNIT_Type unitType = Metric;

    float hex2decNew(char*, int);

    Logger *TCPLogger = nullptr;

    int THSensors = 12;

    union{
        quint32 uTemp;
        char uByte[4];
    }u;

private slots:
    void onConnected();
    void onDisconnected();
    void onSocketStateChange(QAbstractSocket::SocketState socketState);
    void Tempe_onSocketReadyRead();
    void Cmd_onSocketReadyRead();

    void Laser1_SocketRead();
    void Laser2_SocketRead();

    void Laser_onSocketReadyRead_Wire();

    void Pyrometer_onSocketReadyRead();
    //20190925 CBox Tibbo ================>
    void CBox_Cmd_onSocketReadyRead();
    void CBox_Maf_and_Speed_onSocketReadyRead();
    void CBox_Switch_onSocketReadyRead();
    //20190925 CBox Tibbo <================
    void getPWMValue(PWM_Struct*);
    void getXYZDiameter(float*);

    void getPyrometer(qreal);

    void getExtSignalConfig(External_signal*);
    void getResetExtSignal(External_signal*);

    void getLV1Signal(bool,bool,bool,bool);
    void getLV1S1(bool);
    void getLV1S2(bool);
    void getLV1S3(bool);
    void getLV1S4(bool);
    void getUnit(UNIT_Type);

    void getTibboFlag(bool);

    void getTHSensor(int);
    void getOffset(float*);


signals:
    void tcp_thread_connect(QString address, int port);
    void tcp_thread_disconnect(QString address, int port);
    void error(int socketError, const QString &message);
    void sendBackTempValue(double* , double*);
    void sendBackCboxTemp(double*, double*);
    void sendBackAirFlow(double);
    void sendBackPWM(PWM_Struct*);
    void sendBackPyro(double);
    void sendBackDiameter(float*);

    void sendXYZDiameter(float*);
    void sendXYDiameter(float*);
    void sendBackXYDiameter(float*);
    void sendBackXYZDiameter(float*);
    void sendBackSpeed(float);

    void sendRunningSignal(bool);
    void sendPyrometer(qreal);

    void sendOffet(float*);
    void sendBackOffet(float*);

};



#endif
