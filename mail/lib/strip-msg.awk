# mode 0 means in headers, 1 means in body, 2 means 
BEGIN{FS=":"; header=1; fluff=0}
header==1 && ($1 == "Received" || $1 == "Resent-Date" || $1 == "Resent-Message-Id" || $1 == "Message-Id" || $1 == "Resent-From") { fluff=1; kill }
header==1 && fluff==1 && $0 ~ /	.*/ { kill }
header==1{fluff=0; print}
NF==0{header=0; fluff=0; print}
header==0{print}
