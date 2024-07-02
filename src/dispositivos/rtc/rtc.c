#include "rtc.h"


rtc_struct rtc_time;

uint8_t mode;

int (rtc_read_set)(){
    if(rtc_read_output(&mode, BINARY_MODE)){
        printf("Error in check_binary_mode() rtc_read_output\n");
        return 1;
    }

    mode &= BINARY_MODE;
    if((rtc_get_time(&rtc_time))){
        printf("Error in rtc_read_set() rtc_get_time\n");
        return 1;
    }

    return 0;
}


//obtem a hora atual do RTC
int (rtc_get_time)(rtc_struct *rtc_time_dis){
    uint8_t data;
    if(rtc_read_output(&data, UPDATE_BIT)){
        printf("Error in check_update_in_progress() rtc_read_output\n");
        return 1;
    }

    data &= UPDATE_MODE;

    if(rtc_read_output(&data, SECONDS_BIT)){
        printf("Error in rtc_get_time() rtc_output\n");
        return 1;
    }

    rtc_time_dis->seconds = data;

    if(rtc_read_output(&data, MINUTES_BIT)){
        printf("Error in rtc_get_time() rtc_output\n");
        return 1;
    }

    rtc_time_dis->minutes = data;

    if(rtc_read_output(&data, HOURS_BIT)){
        printf("Error in rtc_get_time() rtc_output\n");
        return 1;
    }

    rtc_time_dis->hours = data;

    if(mode){
        rtc_time.seconds = BINARY(rtc_time.seconds);
        rtc_time.minutes = BINARY(rtc_time.minutes);
        rtc_time.hours = BINARY(rtc_time.hours);
    }

    return 0;    
}


