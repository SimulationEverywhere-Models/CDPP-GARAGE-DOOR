[top]
components : codeCont@CodeCont 
out : incre validCode emerg
in : input_code open_request emerg_open 
Link : input_code input_code@codeCont
Link : open_request open_request@codeCont
Link : emerg_open emerg_open@codeCont
Link : incre@codeCont incre
Link : validCode@codeCont validCode
Link : emerg@codeCont emerg

[codeCont]
passcode : 45968
