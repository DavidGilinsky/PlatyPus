//
// Created by gilinsky on 11/23/17.
//

#ifndef PLATYPUS_SENSOR_DATA_H
#define PLATYPUS_SENSOR_DATA_H

struct sensorData {
    struct RPM {
        int value;
        unsigned char sourceNode[6];
        bool valid;
    };
    struct speedWheel {
        int value;
        unsigned char sourceNode[6];
        bool valid;
    };
    struct speedGPS {
        int value;
        unsigned char sourceNode[6];
        bool valid;
    };
    struct temperatureOutside {
        int value;
        unsigned char sourceNode[6];
        bool valid;
    };
    struct temperatureCabin {
        int value;
        unsigned char sourceNode[6];
        bool valid;
    };
    struct temperatureWater {
        int value;
        unsigned char sourceNode[6];
        bool valid;
    };
    struct temperatureTransmission {
        int value;
        unsigned char sourceNode[6];
        bool valid;
    };
    struct pressureFrontAir {
        int value;
        unsigned char sourceNode[6];
        bool valid;
    };
    struct pressureRearAir {
        int value;
        unsigned char sourceNode[6];
        bool valid;
    };
    struct pressureOil {
        int value;
        unsigned char sourceNode[6];
        bool valid;
    };
};




#endif //PLATYPUS_SENSOR_DATA_H
