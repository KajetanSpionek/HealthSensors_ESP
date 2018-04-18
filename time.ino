void initTime() {
    time_t epochTime;
    // Read time from web
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
            // Serial.println(ctime(&epochTime));
            // Send frame to STM with time
            sendTime(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
            sendDate(timeinfo->tm_mday, timeinfo->tm_mon, timeinfo->tm_year, timeinfo-> tm_wday);
            break;
        }
    }
}