[top]
components : alarmGen@AlarmGen 
out : minor_alarm major_alarm
in : unauth_attempt emerg alarm_reset
Link : unauth_attempt unauth_attempt@alarmGen
Link : emerg emerg@alarmGen
Link : alarm_reset alarm_reset@alarmGen
Link : minor_alarm@alarmGen minor_alarm
Link : major_alarm@alarmGen major_alarm
