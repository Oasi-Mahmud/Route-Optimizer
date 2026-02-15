#ifndef mode_H
#define mode_H

#define EARTH_RADIUS_KM 6371.0
#define PI 3.14159265358979323846
#define WALK_SPEED_KMH 2.0
#define MAX_WALK_DISTANCE_KM 0.1  
#define VEHICLE_SPEED_PROBLEM5_KMH 10.0
#define VEHICLE_SPEED_KMH 30.0
#define SCHEDULE_INTERVAL_MIN 15  
#define SCHEDULE_START_MIN (6 * 60)  
#define SCHEDULE_END_MIN (23 * 60)   

#define CAR_SPEED_PROBLEM6_KMH 20.0
#define METRO_SPEED_PROBLEM6_KMH 15.0
#define BIKOLPO_SPEED_PROBLEM6_KMH 10.0
#define UTTARA_SPEED_PROBLEM6_KMH 12.0

#define BIKOLPO_INTERVAL_MIN 20
#define BIKOLPO_START_MIN (7 * 60)    
#define BIKOLPO_END_MIN (22 * 60)     

#define UTTARA_INTERVAL_MIN 10
#define UTTARA_START_MIN (6 * 60)     
#define UTTARA_END_MIN (23 * 60)     

#define METRO_INTERVAL_MIN 5
#define METRO_START_MIN (1 * 60)      
#define METRO_END_MIN (23 * 60)    

typedef enum
{
    MODE_WALK,
    MODE_METRO,
    MODE_CAR,
    MODE_BIKOLPO,
    MODE_UTTARA
} Mode;

const char* getModeName(Mode mode);

#endif