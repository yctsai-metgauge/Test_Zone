#ifndef ROD_CHECK_H
#define ROD_CHECK_H

#include <qpoint.h>
#include <QString>
#include <QPointF>

#define MAXIMUM_AXIS_NUM (6)
#define metgauge_offset   0
#define deviation_range 0.5

#define InTomm (25.4)
#define FeetToMeter (0.3048)
#define BondsFeetToKgMeter (1.488164)
#define CToF(C) (C*9/5+32)
#define FToC(F) ((F-32)*5/9)
#define ImToMetDensity (16.0184634)

#define AIRFLOWCNTLIMIT (5)

#define TEMP_SENSOR_NUM (20)
#define TEMP_SENSOR_NUM_ROD (9)
#define TEMP_SENSOR_NUM_BAR (12)
#define TEMP_SENSOR_NUM_WIRE (5)

#define POLAR_EXTRA_RANGE (1.1)

// Queue
#define Diagram_MAX_LENGTH 601
//#define Billet_Minute 5 // no longer used, replaced by billet_max_entries

#define Master_IP_Address "192.168.50.99"
#define Slave_IP_Address  "192.168.50.100"
#define CBox_IP_Address   "192.168.50.101"


// Thermal compensation
#define MarkerNum 2
#define MaxAxeNum 6

// T/H senseor number
#define THSENSOR 9

//Level 2 connection definiation
#define CONNECT_SUCCESS 0xA0
#define PRESET_TELEGRAM 0xAA
#define STRING_TELEGRAM 0xAB
#define SUMMARY_TELEGRAM 0xAC

//Web Application Definiation
#define HISTOGRAM_MAX_NUM 200

#ifdef Q_OS_WIN
    #define CONFIGPATH ("\\Metgauge.ini")
    #define SAVEDCONFIG ("\\MetgaugeSaved.ini")
    #define CALIB_HIST ("\\CalibHist.ini")
#else
    #define CONFIGPATH ("/scripts/Metgauge.ini")
    #define SAVEDCONFIG ("/scripts/MetgaugeSaved.ini")
    #define CALIB_HIST ("/scripts/CalibHist.ini")
#endif

#define DataBase

QPointF trans(int angle);

enum PAGE_STATUS
{
  STATUS_INIT,
  STATUS_MAIN_PAGE,
  STATUS_DIAGRAM_PAGE,
  STATUS_PRESETS_PAGE,
  STATUS_RETRIEVAL_PAGE,
  STATUS_COMBINED_LINE_PAGE,
  STATUS_BILLETTREND_PAGE,
  STATUS_REBAR_PAGE,
  STATUS_DIGNOSIS_PAGE,
  STATUS_LOGVIEWER_PAGE,
  STATUS_EXTERNAL_PAGE,
  STATUS_COOLING_PAGE
};

enum GAUGE_DATA_STATUS
{
        GAUGE_DATA_DONE,
        GAUGE_DATA_START,
        GAUGE_DATA_PROCESS
};

enum PROCESS_STATUS
{
        STATUS_1,
        STATUS_2,
        STATUS_3,
        STATUS_4,
        STATUS_DONE
};

enum Channel_Type
{
        Negative,
        Positive
};

enum Switch_Type
{
        SingleType,
        DualType
};

enum SocketState
{
        UnconnectedState,
        HostLookupState,
        ConnectingState,
        ConnectedState,
        BoundState,
        ListeningState,
        ClosingState
};

typedef  enum
{
    Round,
    Rebar
}Material_Type;

typedef enum
{
    Imperial,
    Metric
}UNIT_Type;

typedef  enum
{
    ROD,
    BAR,
    WIRE,
    ROD_40,
    CG
}ATON_TYPE;

typedef  enum
{
    SERVER_NOT_RUNNING,
    SERVER_CREATED,
    CLIENT_CONNECTED
}Lv2States;

typedef  enum
{
    US,
    DE,
    TW,
    CN
}Language;

typedef  enum
{
    WEB_PRESET,         // Preset value
    WEB_REAL_DATA,      // Diameter and temperature
    WEB_SUMMARY,        // SummaryTelegram
    WEB_BAR,            // Histogram
    WEB_REBAR           // Rebar value
}WEB_TYPE;

typedef struct
{
    WEB_TYPE type;
    uint DeviceID;
    unsigned int axisNum;
    double diameter[MAXIMUM_AXIS_NUM];
    double temperature;
    double max;
    double min;
    double ovality;
}WEB_RealData;

typedef struct
{
    WEB_TYPE type;
    uint DeviceID;
    double column[HISTOGRAM_MAX_NUM] = {0};
    int count[HISTOGRAM_MAX_NUM] = {0};
}WEB_Bar;

typedef struct
{
    WEB_TYPE type;
    uint DeviceID;
    float coreDiameter;
    float ribHeight;
    float area;
    float meterWeight;
}WEB_Rebar;

typedef struct
{
    bool ExternalFlag;
    bool SpeedType;  //0:off 1:on
    bool SpeedActive;//0:off 1:on
    bool SwitchType; //0:single   1:dual
    bool Ch1Type;    //0:negative 1:positive
    bool Ch2Type;    //0:negative 1:positive
    bool SwitchActive;	//0:off 1:on
    quint8 temperature;
    quint8 temperatureType;
    qreal VoltageToSpeed;
    qreal CurrentToSpeed;
    qreal CountToSpeed;
}External_signal;

typedef struct
{
    quint16 Echo;
    External_signal	ePkt;
    quint8 checksum;
    quint8 endchar;
}External_Pkt;

typedef struct{
    //Diametr Tolerance
    qreal tolerance_low;
    qreal tolerance_middle;
    qreal tolerance_high;
    qreal tolerance_low_warning;
    qreal tolerance_high_warning;
    qreal tolerance_times;
    qreal warningRatio;
    QString diameter_setting_mode;

    //for asymmetric_percentage mode(AVI)
    qreal upper_warning_percent=0;
    qreal lower_warning_percent=0;
    qreal lower_limit_percent=0;


    qreal ova_warning;
    qreal ova_tolerance;

    //Preset Position Parameter
    qreal speed;
    qreal skip_head;
    qreal skip_tail=0;

    //Temperature Warning Threshold
    // Deprecated: These not preset for billet
    qreal outside_temperature_high=0.0;
    qreal outside_temperature_low=0.0;
    qreal inside_temperature_low=0.0;
    qreal inside_temperature_high=0.0;
    qreal cbox_temperature=0.0;
    qreal blower_temperature=0.0;

    //Coefficient for temperature compensation
    qreal steel_temperature;
    qreal shrinkage_info;

    //Rebar Preset Value
    qreal ribHeightNominal;
    qreal ribHeightTolerance;
    qreal areaNominal;
    qreal areaTolerance;
    qreal meterWeightNominal;
    qreal meterWeightTolerance;
    qreal cross_section_len;
    qreal density;

    QString Batch_ID;
    QString Billet_Count;
    //char FinishDate[256] = {0};
    QString FinishDate;
    QString csvPath;
    QString startTime;

    // Deprecated
    QString temperatureCsvPath;

}Presets_Struct;

typedef struct{
    QString BatchID;
    QString BilletCnt;
    float max[MAXIMUM_AXIS_NUM] = {0};
    float min[MAXIMUM_AXIS_NUM] = {0};
    float avg[MAXIMUM_AXIS_NUM] = {0};
    int measureCnt = 0;
    int inTolerCnt = 0;
    int inWarnCnt = 0;
    int outTolerCnt = 0;
    int outWarnCnt = 0;


}Summary_Tele_Struct;

typedef  struct{
 /*   double RibHeightNormal;
    double RibHeightTolerance;
    double AreaNormal;
    double AreaTolerance;
    double MeterWeightNormal;
    double MeterWeightTolerance;*/

    //double ToleranceTimes;
    uint ALG_TYPE;
    int SkipNumber;
    int Mc;
}Rebar_Config_Struct;

typedef struct{
    bool pwm_manual = false;
    bool pwm_stop = false;
    bool pwm_init_flag = false;
    int  pwm_report_cnt;
    qreal pwm_value;
    qreal pwm_current;
    qreal pwm_value_1;
    qreal pwm_current_1;
    qreal pwm_value_2;
    qreal pwm_current_2;
} PWM_Struct;

//union{
//    quint32 uTemp;
//    char uByte[4];
//}u;

typedef enum
{
    EXTREME,
    OVALITY,
    TEMPERATURE,
    BINDING,
    AXIS,
    CORE,
    RIB,
    AREA,
    WEIGHT
}chartType;

typedef enum
{
    MAIN,
    COMBINE,
    BILLET,
    DIAGRAM,
    REBAR
}chartPage;

struct Point  {
    double x, y;
};


#endif // ROD_CHECK_H
