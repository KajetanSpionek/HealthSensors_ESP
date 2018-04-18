void initTime() {
    time_t epochTime;
    configTime(7200, 0, "pool.ntp.org", "time.nist.gov");

    while (true) {
        epochTime = time(NULL);
        struct tm* timeinfo;
        if (epochTime == 0) {
            //Fetching NTP epoch time failed! Waiting 2 seconds to retry
            delay(2000);
        } else {
            // Fetched NTP
            epochTime = time(NULL);
            timeinfo = localtime(&epochTime);
            while(timeinfo->tm_year == 70) {
                delay(100);
                epochTime = time(NULL);
                timeinfo = localtime(&epochTime);
            }
            Serial.println(ctime(&epochTime));
            Serial.println(timeinfo->tm_hour);
            Serial.println(timeinfo->tm_min);
            Serial.println(timeinfo->tm_sec);
            break;
        }
    }
}