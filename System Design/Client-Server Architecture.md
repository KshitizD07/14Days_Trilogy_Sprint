# Client-Server Architecture:

* In CSA, the client which could be the mobile or laptop's browser, sends a request to the server over the internet, this request is then processed by the server and is replied with appropriate response (like sending back the asked data).
* The request that the client sends contains the **URL, Headers and Body.**
* ### URL(Uniform Resource Locator)-

  * It's just and address: https://www.amazon.com:443/products/laptop?color=silver\&sort=price#reviews

&#x09;                     (protocol) (domain/host)(port)(path)(query parameters) (fragments)         

1. #### &#x20;Protocols-

&#x09;-https://:it is insecure, data is sent in plain English

&#x09;Ex- "password123"

&#x09;-https://:the data is encrypted with SSL/TLS

&#x09;Ex- "x7$9mK!p3"

#### 

#### 2\.  Domain-

&#x09;-The human readable address of the server. These are translated to IP addresses using DNS.

&#x09;-These can be mail server(mail.google.com), API server(api.twitter.com), CDN(cdn.netflix.com)



#### 3\.  Port-

&#x09;-These are usually hidden in URLs, they send the request to specific process.



#### 4\.  Path-

&#x09;-The specific resource you're requesting on the server.



#### 5\.  Query Parameters-

&#x09;-This is the extra data sent to filter/modify response. The "?" starts the query string.

&#x09;(key1=value)First parameter, \& is used as separator.





##### What Actually sits in an HTTP Request:

&#x09;POST /api/login HTTP/1.1

&#x09;Host: www.facebook.com

&#x09;User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64)

&#x09;Accept: application/json

&#x09;Content-Type: application/json

&#x09;Content-Length: 57

&#x09;Cookie: session\_id=abc123; user\_pref=dark\_mode

&#x09;Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...



&#x09;{

&#x20; 	"email": "john@example.com",

&#x20; 	"password": "secret123"

&#x09;}	







POST /api/login HTTP/1.1

│    │          │

│    │          └─ HTTP version

│    └─ Path (resource being accessed)

└─ Method (what action to perform)







#### Headers:

&#x09;-These are the metadata about the requests, for one server can host multiple sites.

&#x09;-It also identifies your browser and OS, and then might send response different for both.

&#x09;	Mobile User-Agent → Simpler HTML

&#x09;	Desktop User-Agent → Full-featured HTML



&#x09;-It tells server what format you wants back, could be Application/json.

&#x09;	Accept: application/json → Send me JSON

&#x09;	Accept: text/html → Send me HTML

&#x09;	Accept: image/png → Send me an image



&#x09;-It tells server what format you're sending.

&#x09;	Content-Type: application/json → Body is JSON

&#x09;	Content-Type: application/x-www-form-urlencoded → Body is form data

&#x09;	Content-Type: multipart/form-data → Body includes files (like photo upload)



###### \-Cookie:session\_id=abc123; user\_pref=dark\_mode:

&#x09;-These are small pieces of information the server asked your browser to remember.

&#x09;-Sent automatically with every request.

&#x09;-This is how server knows who the user is.









### What Actually sits in an HTTP Response:

&#x09;Date: Mon, 27 Jul 2024 12:28:53 GMT

&#x09;Server: Apache/2.4.1

&#x09;Content-Type: application/json

&#x09;Content-Length: 128

&#x09;Set-Cookie: session\_id=xyz789; Expires=Wed, 09 Jun 2025 10:18:14 GMT; HttpOnly; Secure

&#x09;Cache-Control: no-cache, no-store, must-revalidate

&#x09;Access-Control-Allow-Origin: https://trusted-site.com

&#x09;{

&#x20; 		"success": true,

&#x20; 		"user": {

&#x20;   		"id": 12345,

&#x20;   		"name": "John Doe",

&#x20;   		"email": "john@example.com"

&#x20; 	},

&#x20; 	"token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."

&#x09;}





&#x09;HTTP/1.1 200 OK

&#x20;        │   │

&#x20;        │   └─ Status message

&#x20;        └─ Status code



##### &#x09;Common Status Code:

&#x09;	200 OK-Success 			Login Successful

&#x09;	201 Created    			New User registered

&#x09;	204 No Content			Deleted Successfully (no data to return)

&#x09;	301 Moved Permanently		

&#x09;	302 Temporary Redirect		Maintenance Mode

&#x09;	400 Bad Request 		You sent invalid JSON

&#x09;	401 Unauthorized 		You're not logged in

&#x09;	403 Forbidden 			You're logged in but don't have permission

&#x09;	404 Not Found 			Page doesn't exists

&#x09;	429 Too many requests 		Rate limit exceeded

&#x09;	500 Internal server error 	Server code crashed

&#x09;	502 Bad Gateway 		Server is down/Unreachable

&#x09;	503 Service Unavailable 	Server Overloaded 		















































