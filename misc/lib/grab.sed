/^;/s///
/^[dD] /s//Date: /
/^n /s//Name: /
/^t /s//Title: /
/^o /s//Organization: /
/^k /s//Keyword(s): /
/^div /s//Division: /
/^1 /s//Address	/
/^2 /s//	/
/^3 /s//	/
/^4 /s//	/
/^e /s//Email: /
/^p /s///
/^hp /s/^hp \(.*\)/\1 home/
/^wp /s/^wp \(.*\)/\1 work/
/^fax /s/^fax \(.*\)/\1 fax/
/^pager /s/^pager \(.*\)/\1 pager/
/^TWX /s/^fax \(.*\)/\1 TWX/
/^telex /s/^fax \(.*\)/\1 telex/
/\\f[BI]/s//(/
/\\fR/s//)/
