//
// Created by gilinsky on 11/23/17.
//

#ifndef PLATYPUS_SENSOR_DATA_H
#define PLATYPUS_SENSOR_DATA_H

struct sensorData {
    int RPM;
    int speedWheel;
    int speedGPS;
    float temperatureOutside;
    float temperatureCabin;
    float temperatureWater;
    float temperatureTransmission;
    int pressureFrontAir;
    int pressureRearAir;
    int pressureOil;
};

#endif //PLATYPUS_SENSOR_DATA_H
