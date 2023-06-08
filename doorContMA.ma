[top]
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







