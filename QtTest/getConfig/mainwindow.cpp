#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getConfig()
{
    QString savedConfigFilePath;
#ifdef Q_OS_WIN
    savedConfigFilePath = QApplication::applicationDirPath() + SAVEDCONFIG;
#else  //linux
    savedConfigFilePath = SAVEDCONFIG;
#endif

    QString filename = "";
    if (QFile::exists(savedConfigFilePath)) // if MetgaugeSaved.ini exists
        filename = SAVEDCONFIG; // use MetgaugeSaved.ini
    else
        filename = CONFIGPATH; // use Metgauge.ini

#ifdef Q_OS_WIN
    QSettings Config(QApplication::applicationDirPath() + filename, QSettings::IniFormat);
#else  //linux
    QSettings Config(filename, QSettings::IniFormat);
#endif

    qDebug()<<"load config file="<<filename;

    Config.setIniCodec("UTF-8");

    // ATON Basic setting
    Config.beginGroup("00_ATON_SETTING");
    configVersion = Config.value("000_Version").toString();
    QString latestVersion = "v2021_10_8";

    if (configVersion != latestVersion) {
        QMessageBox::warning(this, tr("Config error"),tr("Please use ver ") +latestVersion+  tr(" config file."), QMessageBox::Yes);
        //Config.endGroup();
        //return;
    }

    AxisNum                  = Config.value("010_AXIS_NUM").toUInt();
    sensorSequen[0]          = Config.value("011_AXIS_1").toInt();
    sensorSequen[1]          = Config.value("012_AXIS_2").toInt();
    sensorSequen[2]          = Config.value("013_AXIS_3").toInt();
    sensorSequen[3]          = Config.value("014_AXIS_4").toInt();
    sensorSequen[4]          = Config.value("015_AXIS_5").toInt();
    sensorSequen[5]          = Config.value("016_AXIS_6").toInt();
    MonitorSize              = Config.value("020_MONITOR_SIZE").toUInt();
    materialType             = Config.value("030_MATERIAL_TYPE").toInt();
    traffic_light_reset_time = Config.value("040_STATUS_RESET").toInt();
    config_language          = Config.value("050_LANGUAGE").toString().toUpper();
    metric_or_imperial       = Config.value("060_METRIC_OR_IMPERIAL").toString();
    productionTemp           = Config.value("070_PRODUCTION_TEMPERATURE").toInt();
    billet_or_coil           = Config.value("080_BILLET_OR_COIL").toString();
    billet_max_entries       = Config.value("090_BATCH_MAX_ENTRIES").toInt(); // for endless batches set billet length
    scan_rate                = Config.value("100_SCAN_RATE", 0).toInt();
    roundingDigit            = Config.value("110_ROUNDINGDIGIT").toInt();
    no_hdd                   = Config.value("120_NO_HDD", false).toBool();
    maxDiameter              = Config.value("121_MaxDiameter").toDouble();
    save_raw_diameter        = Config.value("122_SAVE_RAW_DIAMETERS").toBool();
    Config.endGroup();

    qDebug()<<"010_AXIS_NUM"    << AxisNum;
    qDebug()<<"011_AXIS_1"      << sensorSequen[0];
    qDebug()<<"012_AXIS_2"      << sensorSequen[1];
    qDebug()<<"013_AXIS_3"      << sensorSequen[2];
    qDebug()<<"014_AXIS_4"      << sensorSequen[3];
    qDebug()<<"015_AXIS_5"      << sensorSequen[4];
    qDebug()<<"016_AXIS_6"      << sensorSequen[5];
    qDebug()<<"020_MONITOR_SIZE"  << MonitorSize;
    qDebug()<<"030_MATERIAL_TYPE" << materialType;
    qDebug()<<"040_STATUS_RESET"  << traffic_light_reset_time;
    qDebug()<<"050_LANGUAGE"      << config_language;
    qDebug()<<"060_METRIC_OR_IMPERIAL" << metric_or_imperial;
    qDebug()<<"070_PRODUCTION_TEMPERATURE" << productionTemp;
    qDebug()<<"080_BILLET_OR_COIL"    << billet_or_coil;
    qDebug()<<"090_BATCH_MAX_ENTRIES" << billet_max_entries;
    qDebug()<<"100_SCAN_RATE"     << scan_rate;
    qDebug()<<"110_ROUNDINGDIGIT" << roundingDigit;
    qDebug()<<"120_NO_HDD"        << no_hdd;
    qDebug()<<"121_MaxDiameter"   << maxDiameter;

    Config.beginGroup("01_CALIB_SETTING");
    calib_small                              = Config.value("01_CALIB_SMALL").toDouble();
    calib_big                                = Config.value("02_CALIB_BIG").toDouble();
    Config.endGroup();

    qDebug()<<"01_CALIB_SMALL" << calib_small;
    qDebug()<<"02_CALIB_BIG" << calib_big;


    //Preset default value
    Config.beginGroup("02_PRESET_DEFAULT_SETTING");
    PresetMainWindow->speed                  = Config.value("01_SPEED").toDouble();
    PresetMainWindow->steel_temperature      = Config.value("02_TEMPERATURE").toDouble();
    PresetMainWindow->skip_head              = Config.value("03_SKIP_HEAD").toDouble();
    PresetMainWindow->skip_tail              = Config.value("04_SKIP_TAIL").toDouble();
    PresetMainWindow->cross_section_len      = Config.value("05_REF_LENGTH").toDouble();
    PresetMainWindow->density                = Config.value("06_DENSITY").toDouble();
    PresetMainWindow->ova_tolerance          = Config.value("07_OVA_TOLERANCE").toDouble();
    PresetMainWindow->ova_warning            = Config.value("08_OVA_WARNING").toDouble();
    PresetMainWindow->shrinkage_info         = Config.value("09_COEFFICIENT").toDouble();
    PresetMainWindow->diameter_setting_mode  = Config.value("10_DIAMETER_SETTING_MODE").toString().toLower();
    PresetMainWindow->warningRatio           = Config.value("11_WARNING_RANGE_RATIO").toDouble();
    PresetMainWindow->tolerance_high         = Config.value("12_TOLERANCE_HIGH").toDouble(); // this is called "nominal" in asymmetric_percentage mode
    PresetMainWindow->tolerance_high_warning = Config.value("13_TOLERANCE_HIGH_WARNING").toDouble();
    PresetMainWindow->tolerance_middle       = Config.value("14_TOLERANCE_MIDDLE").toDouble();
    PresetMainWindow->tolerance_low_warning  = Config.value("15_TOLERANCE_LOW_WARNING").toDouble();
    PresetMainWindow->tolerance_low          = Config.value("16_TOLERANCE_LOW").toDouble();
    PresetMainWindow->upper_warning_percent  = Config.value("171_TOLERANCE_HIGH_WARNING_PERCENT", 2).toDouble();
    PresetMainWindow->lower_warning_percent  = Config.value("172_TOLERANCE_LOW_WARNING_PERCENT", 4).toDouble();
    PresetMainWindow->lower_limit_percent    = Config.value("173_LOWER_LIMIT_PERCENT", 6).toDouble();
    PresetMainWindow->ribHeightNominal       = Config.value("181_RIB_HEIGHT_NORMAL").toDouble();
    PresetMainWindow->ribHeightTolerance     = Config.value("182_RIB_HEIGHT_TOLERANCE").toDouble();
    PresetMainWindow->areaNominal            = Config.value("183_AREA_NORMAL").toDouble();
    PresetMainWindow->areaTolerance          = Config.value("184_AREA_TOLERANCE").toDouble();
    PresetMainWindow->meterWeightNominal     = Config.value("185_METER_WEIGHT_NORMAL").toDouble();
    PresetMainWindow->meterWeightTolerance   = Config.value("186_METER_WEIGHT_TOLERANCE").toDouble();
    RebarConfigStruct->ALG_TYPE              = Config.value("19_REBAR_ALG_ENUM").toUInt();
    RebarConfigStruct->SkipNumber            = Config.value("20_SKIP_NUMBER").toInt();
    RebarConfigStruct->Mc                    = Config.value("21_MC").toInt();
    Config.endGroup();

    qDebug()<<"01_SPEED"       << PresetMainWindow->speed;
    qDebug()<<"02_TEMPERATURE" << PresetMainWindow->steel_temperature;
    qDebug()<<"03_SKIP_HEAD"   << PresetMainWindow->skip_head ;
    qDebug()<<"04_SKIP_TAIL"   << PresetMainWindow->skip_tail;
    qDebug()<<"05_REF_LENGTH"  << PresetMainWindow->cross_section_len;
    qDebug()<<"06_DENSITY"     << PresetMainWindow->density;
    qDebug()<<"07_OVA_TOLERANCE" << PresetMainWindow->ova_tolerance;
    qDebug()<<"08_OVA_WARNING"   << PresetMainWindow->ova_warning;
    qDebug()<<"09_COEFFICIENT"   << PresetMainWindow->shrinkage_info;
    qDebug()<<"10_DIAMETER_SETTING_MODE" << PresetMainWindow->diameter_setting_mode;
    qDebug()<<"11_WARNING_RANGE_RATIO"   << PresetMainWindow->warningRatio;
    qDebug()<<"12_TOLERANCE_HIGH"        << PresetMainWindow->tolerance_high;
    qDebug()<<"13_TOLERANCE_HIGH_WARNING" << PresetMainWindow->tolerance_high_warning;
    qDebug()<<"14_TOLERANCE_MIDDLE"       << PresetMainWindow->tolerance_middle;
    qDebug()<<"15_TOLERANCE_LOW_WARNING"  << PresetMainWindow->tolerance_low_warning;
    qDebug()<<"16_TOLERANCE_LOW"          << PresetMainWindow->tolerance_low;
    qDebug()<<"171_TOLERANCE_HIGH_WARNING_PERCENT" << PresetMainWindow->upper_warning_percent;
    qDebug()<<"172_TOLERANCE_LOW_WARNING_PERCENT"  << PresetMainWindow->lower_warning_percent;
    qDebug()<<"173_LOWER_LIMIT_PERCENT"    << PresetMainWindow->lower_limit_percent;
    qDebug()<<"181_RIB_HEIGHT_NORMAL"      << PresetMainWindow->ribHeightNominal;
    qDebug()<<"182_RIB_HEIGHT_TOLERANCE"   << PresetMainWindow->ribHeightTolerance;
    qDebug()<<"183_AREA_NORMAL"            << PresetMainWindow->areaNominal;
    qDebug()<<"184_AREA_TOLERANCE"         << PresetMainWindow->areaTolerance;
    qDebug()<<"185_METER_WEIGHT_NORMAL"    << PresetMainWindow->meterWeightNominal;
    qDebug()<<"186_METER_WEIGHT_TOLERANCE" << PresetMainWindow->meterWeightTolerance;
    qDebug()<<"19_REBAR_ALG_ENUM"     << RebarConfigStruct->ALG_TYPE;
    qDebug()<<"20_SKIP_NUMBER"        << RebarConfigStruct->SkipNumber;
    qDebug()<<"21_MC"                 << RebarConfigStruct->Mc;


    Config.beginGroup("03_OPTIONAL_SETTING");
    // LV1
    lv1update                                = Config.value("01_LV1update").toInt();
    lv1_signal->ExternalFlag                 = Config.value("02_EXTERNAL_FLAG").toBool();
    lv1_signal->SpeedActive                  = Config.value("03_EXT_SPEED").toBool();
    lv1_signal->SpeedType                    = Config.value("04_EXT_SPEED_TYPE").toBool();
    lv1_signal->SwitchActive                 = Config.value("05_EXT_SWITCH").toBool();
    lv1_signal->SwitchType                   = Config.value("06_EXT_SWITCH_TYPE").toBool();
    lv1_signal->Ch1Type                      = Config.value("071_EXT_SWITCH_CH1").toBool();
    lv1_signal->Ch2Type                      = Config.value("072_EXT_SWITCH_CH2").toBool();
    lv1_signal->VoltageToSpeed               = Config.value("08_EXT_SPEED_VOLTAGE_VARIABLE").toDouble();
    lv1_signal->CountToSpeed                 = Config.value("09_EXT_SPEED_COUNT_VARIABLE").toDouble();
    lv1_signal->CurrentToSpeed               = Config.value("10_EXT_SPEED_CURRENT_VARIABLE").toDouble();
    lv1_signal->temperature                  = Config.value("11_EXT_TMPERATURE").toUInt();
    lv1_signal->temperatureType              = Config.value("12_EXT_TMPERATURE_TYPE").toUInt();
    // Web
    webUpdateRate                            = Config.value("13_UPDATE_RATE").toInt();
    m_adminDialog->m_lv2Server->DeviceID     = Config.value("14_DEVICE_ID").toUInt();
    Config.endGroup();


    qDebug()<<  "01_LV1update"                 << lv1update;
    qDebug()<<  "02_EXTERNAL_FLAG"             << lv1_signal->ExternalFlag ;
    qDebug()<<  "03_EXT_SPEED"                 << lv1_signal->SpeedActive;
    qDebug()<<  "04_EXT_SPEED_TYPE"            << lv1_signal->SpeedType;
    qDebug()<<  "05_EXT_SWITCH"                << lv1_signal->SwitchActive;
    qDebug()<<  "06_EXT_SWITCH_TYPE"           << lv1_signal->SwitchType;
    qDebug()<<  "071_EXT_SWITCH_CH1"           << lv1_signal->Ch1Type;
    qDebug()<<  "072_EXT_SWITCH_CH2"           << lv1_signal->Ch2Type;
    qDebug()<<  "08_EXT_SPEED_VOLTAGE_VARIABLE"<< lv1_signal->VoltageToSpeed;
    qDebug()<<  "09_EXT_SPEED_COUNT_VARIABLE"  << lv1_signal->CountToSpeed;
    qDebug()<<  "10_EXT_SPEED_CURRENT_VARIABLE"<< lv1_signal->CurrentToSpeed;
    qDebug()<<  "11_EXT_TMPERATURE"            << lv1_signal->temperature;
    qDebug()<<  "12_EXT_TMPERATURE_TYPE"       << lv1_signal->temperatureType;
    qDebug()<<  "13_UPDATE_RATE"               << webUpdateRate;
    qDebug()<<  "14_DEVICE_ID"                 << m_adminDialog->m_lv2Server->DeviceID;

    Config.beginGroup("04_ERROR_LOG_SETTING");
    //Temperature warning setting
    warningDiff                              = Config.value("01_WARNING_TEMPERATURE_DIFF").toString();
    BUILT_IN_PYROMETER                       = Config.value("02_BULIT_IN_PYROMETER").toBool();
    airflowLimit                             = Config.value("03_AIRFLOW_WARN_VALUE").toDouble();
    Config.endGroup();

    qDebug()<<"01_WARNING_TEMPERATURE_DIFF" << warningDiff;
    qDebug()<<"02_BULIT_IN_PYROMETER"       << BUILT_IN_PYROMETER;
    qDebug()<<"03_AIRFLOW_WARN_VALUE"       << airflowLimit;

    Config.beginGroup("05_CSV_FORMAT_SETTING");
    csv_separation_char_str                  = Config.value("01_CSV_SEPARATION_CHAR").toString();
    csv_decimal_char_str                     = Config.value("02_CSV_DECIMAL_CHAR").toString();
    Config.endGroup();

    qDebug()<<"01_CSV_SEPARATION_CHAR"  << csv_separation_char_str;
    qDebug()<<"02_CSV_DECIMAL_CHAR"     << csv_decimal_char_str;

    Config.beginGroup("06_DISPLAY_SETTING");
    histClassNum                             = Config.value("011_HIST_CLASS_NUM").toInt();
    histRange                                = Config.value("012_HIST_RANGE").toDouble();
    show_raw_data_browser                    = Config.value("02_SHOW_RAW_DATA_BROWSER", 0).toBool();
    Uarea                                    = Config.value("031_UAREA").toDouble();
    Carea                                    = Config.value("032_CAREA").toDouble();
    Larea                                    = Config.value("033_LAREA").toDouble();
    polarMagnify                             = Config.value("04_POLAR_DIAGRAM_MAGNIFY").toDouble();
    show_diameter_average                    = Config.value("05_SHOW_DIAMETER_AVERAGE").toBool();
    show_temperature_value                   = Config.value("06_SHOW_TEMPERATURE_VALUE", 0).toBool();
    billetTrendFlag                          = Config.value("07_HISTOGRAM_FLAG").toBool();
    Config.endGroup();

    qDebug()<<"011_HIST_CLASS_NUM"        << histClassNum;
    qDebug()<<"012_HIST_RANGE"            << histRange;
    qDebug()<<"02_SHOW_RAW_DATA_BROWSER"  << show_raw_data_browser;
    qDebug()<<"031_UAREA"                 << Uarea;
    qDebug()<<"032_CAREA"                 << Carea;
    qDebug()<<"033_LAREA"                 << Larea;
    qDebug()<<"04_POLAR_DIAGRAM_MAGNIFY"  << polarMagnify;
    qDebug()<<"05_SHOW_DIAMETER_AVERAGE"  << show_diameter_average;
    qDebug()<<"06_SHOW_TEMPERATURE_VALUE" << show_temperature_value;
    qDebug()<<"07_HISTOGRAM_FLAG"         << billetTrendFlag;

    Config.beginGroup("07_FILTER");
    SpikeFilterSwitch                        = Config.value("11_SPIKE_FILTER_SWITCH").toBool();
    MovAvgWindowSize                         = Config.value("12_MOVAVG_WINDOWSIZE").toInt();
    SpikeMaxFilterCnt                        = Config.value("13_SPIKE_MAX_FILTER_CNT").toInt();
    SpikeFilTrgOnTh                          = Config.value("14_SPIKE_FILTER_TRIGGER_ON_THD").toDouble();
    SpikeFilTrgOffTh                         = Config.value("15_SPIKE_FILTER_TRIGGER_OFF_THD").toDouble();
    OvalityFilterSwitch                      = Config.value("21_OVALITY_FILTER_SWITCH").toBool();
    ovality_filter_threshold                 = Config.value("22_OVALITY_FILTER_THRESHOLD").toDouble();
    defect_axis                              = Config.value("23_DEFECT_AXIS").toString();
    MinimumFilterSwitch2                     = Config.value("33_MINIMUM_FILTER_2_SWITCH", 0).toBool();
    MinimumFilterWindowSize2                 = Config.value("34_MINIMUM_FILTER_2_WINDOWSIZE", 100).toInt();
    medianSize                               = Config.value("40_MEDIAN_SIZE").toInt();
    avgFilterSwitch                          = Config.value("51_AVG_FILTER_SWITCH").toBool();
    avgFilterSize                            = Config.value("52_AVG_FILTER_WINDOWSIZE").toInt();
    avgFilterDeltaX                          = Config.value("53_AVG_FILTER_DELTAX").toDouble();
    avgFilterDeltaY                          = Config.value("54_AVG_FILTER_DELTAY").toDouble();
    Config.endGroup();

    qDebug()<<"11_SPIKE_FILTER_SWITCH"        << SpikeFilterSwitch;
    qDebug()<<"12_MOVAVG_WINDOWSIZE"          << MovAvgWindowSize;
    qDebug()<<"13_SPIKE_MAX_FILTER_CNT"       << SpikeMaxFilterCnt;
    qDebug()<<"14_SPIKE_FILTER_TRIGGER_ON_THD"<< SpikeFilTrgOnTh;
    qDebug()<<"15_SPIKE_FILTER_TRIGGER_OFF_THD"<< SpikeFilTrgOffTh;
    qDebug()<<"21_OVALITY_FILTER_SWITCH"      << OvalityFilterSwitch;
    qDebug()<<"22_OVALITY_FILTER_THRESHOLD"   << ovality_filter_threshold;
    qDebug()<<"23_DEFECT_AXIS             "   << defect_axis;
    qDebug()<<"33_MINIMUM_FILTER_2_SWITCH"    << MinimumFilterSwitch2;
    qDebug()<<"34_MINIMUM_FILTER_2_WINDOWSIZE"<< MinimumFilterWindowSize2;
    qDebug()<<"40_MEDIAN_SIZE"                << medianSize;
    qDebug()<<"51_AVG_FILTER_SWITCH"          << avgFilterSwitch;
    qDebug()<<"52_AVG_FILTER_WINDOWSIZE"      << avgFilterSize;
    qDebug()<<"53_AVG_FILTER_DELTAX"          << avgFilterDeltaX;
    qDebug()<<"54_AVG_FILTER_DELTAY"          << avgFilterDeltaY;

    // Send signal after initial connect
    writeMainLog(" SPIKE: " + QString::number(SpikeFilterSwitch) +  " CNT: " + QString::number(SpikeMaxFilterCnt) + " SIZE: " + QString::number(MovAvgWindowSize) + " On: " + QString::number(SpikeFilTrgOnTh) + " Off: " + QString::number(SpikeFilTrgOffTh) +
                " OVALITY: " + QString::number(OvalityFilterSwitch) + " " +  QString::number(ovality_filter_threshold) +
                " MINIMUM2: " + QString::number(MinimumFilterSwitch2)+ " " +  QString::number(MinimumFilterWindowSize2));

}
