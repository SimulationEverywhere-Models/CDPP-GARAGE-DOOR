[top]
components : doorCont lightIn@LightIn lightOut@LightOut alarmGen@AlarmGen
in : input_code open_request emerg_open alarm_reset motion light
out : doorOpen minor_alarm major_alarm inlon outlon
Link : input_code input_code@doorCont
Link : open_request open_request@doorCont
Link : emerg_open emerg_open@doorCont
Link : alarm_reset alarm_reset@alarmGen
Link : doorOpen@doorCont doorOpen
Link : validCode@doorCont validCode@lightIn
Link : emerg@doorCont emerg@alarmGen
Link : unauth_attempt@doorCont unauth_attempt@alarmGen
Link : motion motion@lightOut
Link : light light@lightOut
Link : outlon@lightOut outlon
Link : inlon@lightIn inlon
Link : minor_alarm@alarmGen minor_alarm
Link : major_alarm@alarmGen major_alarm


[doorCont]
components : codeCont@CodeCont counter@Counter doorTimer@DoorTimer
in : input_code open_request emerg_open 
out : validCode emerg unauth_attempt doorOpen  
Link : input_code input_code@codeCont
Link : open_request open_request@codeCont
Link : emerg_open emerg_open@codeCont
Link : doorOpen@doorTimer doorOpen
Link : validCode@codeCont validCode
Link : emerg@codeCont emerg
Link : unauth_attempt@counter unauth_attempt
Link : incre@codeCont incre@counter
Link : validCode@codeCont validCode@doorTimer

[codeCont]
passcode : 45968

