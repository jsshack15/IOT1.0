var xmlHttp=createXmlHttpRequestObject();

function createXmlHttpRequestObject(){
	var xmlHttp;
	if(window.ActiveXObject){
	  try{
	    xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
	  } 
	  catch(e){
	  xmlHttp=false;
	  }
	  else{
	    try{
          xmlHttp=newXMLHttpRequest();
	    }
	    catch(e){
	      xmlHttp=false;
	    }
	  }
	}
}
function process(){
	if(xmlHttp.readyState==0||xmlHttp.readyState==4){
	xmlHttp.open("Get", "http://192.168.0.101:80/", true);
	xmlHttp.onreadystatechange=handleServerResponse;
	xmlHttp.send(null);
	}
	else{
	setTimeout('process()',1000);
	}
}
function handleServerResponse(){
     if(xmlHttp.readyState==4){
       if(xmlHttp.status==200){
         xmlResponse=xmlHttp.responseXML;
         xmlDocumentElement=xmlResponse.documentElement;
         message=xmlDocumentElement.firstChild.data;
       }
     }	
}