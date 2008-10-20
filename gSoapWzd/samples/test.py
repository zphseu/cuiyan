import httplib, urllib, mimetools, time

body = """<?xml version="1.0" encoding="UTF-8"?>
<SOAP-ENV:Envelope
 xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"
 xmlns:SOAP-ENC="http://schemas.xmlsoap.org/soap/encoding/"
 xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
 xmlns:xsd="http://www.w3.org/2001/XMLSchema"
 xmlns:ns="calc">
 <SOAP-ENV:Body>
  <ns:divide>
   <a>30</a>
   <b>3</b>
  </ns:divide>
 </SOAP-ENV:Body>
</SOAP-ENV:Envelope>"""


headers = {"Content-type": "text/xml:"}

conn = httplib.HTTPConnection("WY", "8000")
conn.request("POST", "/soap", body, headers)
response = conn.getresponse()
print response.status, response.reason
print response.msg
data = response.read()
print data
conn.close()
