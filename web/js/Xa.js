/* Alessandro Mariotti 
 * alex@xallegro.com
 * @file Xaas.js
 */

var Errors = {
    ArgumentsNumber:"Arguments Number Is Not Valid",
    UrlNotPassed:"URL Parameter Not Passed",
    LoadeTargetIdNotFound:"Request a Loader Without a Target",
    TargetIdDoesNotExist:"Passed Target Id Does Not Exist"
};

var DefaultController="";
var DefaultMethod="POST";
var DefaultAsync="true";
var DefaultTarget="html";
var DefaultJsEval="no";
var	FlowCheck=true;

var AllRequiredFields="Please ensure that all required fields, those with an *(red asterisk), have been completed and formatted correctly!";

function Xa () {
};

Xa.ErrorHandler=function(ErrorName){

    alert(Errors[ErrorName]);
    return false;
};


/*
 * @function XaCall
 * Function to perform AJAX calls
 *
 * @param {string} Controller - The controller to use to build the url if is other than the default 
 * @param {string} Url - The URL to append to the Controller with pairs <param> and <value> the final construct will be: <Controller?param1=value1&param2=value2...>
 * @param {boolean} Sync - True: Async call, False: Sync Call  
 * @param {function} Callback function 
 *
 * @return {Callback function}
 * 
 */

Xa.Call = function(url,type,sync,cb) {

    if (url!=="") {
    
        url.replace("&amp;", "&");
        var url = url;

        if (type==="xml") {
 
            url=url+"&ResType=xml";
        }

        var xmlhttp;

        if (window.XMLHttpRequest) {

            xmlhttp = new XMLHttpRequest();

        } else {

            xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
        }
        
        xmlhttp.onreadystatechange = function () {

            if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {

                if (type==="" || type==="text") {
                    
                    cb(xmlhttp.responseText);

                } else if (type==="xml") {

                    //console.log(xmlhttp.responseXML);
                    cb(xmlhttp.responseXML);
                }

            } else if (xmlhttp.status === 500) {

                alert("error sending async call: "+url);
                cb(0);
            }

        };

        xmlhttp.open("POST", url, sync);
        xmlhttp.send(null);

    } else {

        alert("url parameter is empty");
        cb(0);
    }
};


/*
 * @function XaCallAction
 * Function to call Web Actions
 *
 * @param {string} Controller - The controller to use to build the url if is other than the default 
 * @param {string} Url - The URL to append to the Controller with pairs <param> and <value> the final construct will be: <Controller?param1=value1&param2=value2...>
 * @args  {object} args - Paramenter for the call
 * @param {string} args.FormId - From Id to Send
 * @param {string} args.ResponseType - "Text","Html","HtmlToAppend",
 * @param {string} args.TargetId - The inner tag for Async Calls with returns
 * @param {string} args.CallMethod - POST,GET,""
 * @param {string} args.CallAsync - True,false,""
 * @param {string} args.WithLoader - Show a loader (spinner)
 * @param {string} args.LoaderTargetID - Target Id for the loader
 * @param {string} args.JsEval - "yes" or "no" - enable the JS evaluation
 * @param {string} args.WithAlert - "yes" or "no" - enable the alert
 * @param {string} args.AlertMessage - Alert message or ""
 *
 * @returns {string} 
 * 
 * 
 * Example:
 * var args ={
 *      ResponseType:"Text",
 *      TargetId:"",
 *      CallMethod:"POST",
 *      CallAsync:"true",
 *      WithLoader:"no",
 *      LoaderTargetID:"",
 *      JsEval:"no",
 *      WithAlert:"yes",
 *      AlertMessage:"pippo"
 *  };
*
 *   Xa.CallAction("","obj=objecg&amp;evt=event",args);
 * 
 * 
 */

Xa.CallAction=function (controller,url,args){
    if(args.ResponseType===undefined){ args.ResponseType ="Text"; };
    if(args.CallMethod==="" || args.CallMethod===undefined) { args.CallMethod = DefaultMethod; };
    if(args.CallAsync==="" || args.CallAsync===undefined) { args.CallAsync = DefaultAsync; };
    if(args.WithLoader==="" || args.WithLoader===undefined) { args.WithLoader = "no"; };
    if(args.LoaderTargetID==="" || args.LoaderTargetID===undefined) { args.LoaderTargetID = ""; };
    if(args.JsEval==="" || args.JsEval=== undefined) { args.JsEval = DefaultJsEval;};
    if(args.WithAlert==="" || args.WithAlert===undefined) { args.WithAlert = "no";};
    if(args.TargetId==="" || args.TargetId===undefined) { args.TargetId="html"; }
    if(args.AlertMessage===undefined) { args.AlertMessage=""; }

    if(arguments.length!==3) {Xa.ErrorHandler("ArgumentsNumber"); return false;};

    if(controller==="") {controller = DefaultController;};

    if (url==="") {ErrorHandler("UrlNotPassed"); return false;};

    if(args.FormId===undefined) { args.FormId=""; }

    if (args.FormId!=="") {
        url= url + "&" +XaSerializeForm (args.FormId);
    }

    if(args.WithLoader==="yes") {

        if (args.LoadeTargetId==="") { ErrorHandler("LoadeTargetIdNotFound"); return false; };
        document.getElementById(args.LoadeTargetId).innerHTML = ('<div class="loader"></div>');
    };

    Xa.Call(url,"text",args.CallAsync, function(Response) {

        if (args.ResponseType==="Text"){

            if(args.WithAlert==="yes" && args.AlertMessage==="") {

                alert(Response);

            } else if(args.WithAlert==="yes" && args.AlertMessage!=="") {
 
                alert(args.AlertMessage);

            } else {

                if (document.getElementById(args.TargetId) !==null) {

                    document.getElementById(args.TargetId).value = Response;
                    
                } else {

                    ErrorHandler("TargetIdDoesNotExist"); 
                    return false;
                }

            }

        } else if (args.ResponseType==="Html") {

            if (document.getElementById(args.TargetId) !==null) {

                document.getElementById(args.TargetId).innerHTML = Response;

                if (args.JsEval==="yes") {

			var scripts = document.getElementById(args.TargetId).getElementsByTagName('script');

			var script_array=Array();
			for (var i=0;i<scripts.length;i++) {
				script_array.push(scripts[i].innerHTML);
			}
			for (var i=0;i<script_array.length;i++) {
				eval(script_array[i]);
			}

                }

            } else {
                
                ErrorHandler("TargetIdDoesNotExist"); 
                return false;
                
            }

        } else if (args.ResponseType==="HtmlToAppend") {

            if (document.getElementById(args.TargetId) !==null) {
         
                var OldHtml = document.getElementById(args.TargetId).innerHTML;
                document.getElementById(args.TargetId).innerHTML = OldHtml + Response;
                
                 if (args.JsEval==="yes") {

			var scripts = document.getElementById(args.TargetId).getElementsByTagName('script');

			var script_array=Array();
			for (var i=0;i<scripts.length;i++) {
				script_array.push(scripts[i].innerHTML);
			}
			for (var i=0;i<script_array.length;i++) {
				eval(script_array[i]);
			}

                }
                
            } else {

                ErrorHandler("TargetIdDoesNotExist"); 
                return false;
            }

        }

    });
     
};

Xa.IncludeHtmlFile = function(Url,TargetId) {

    Xa.Call(Url,"text",true ,function(Response) {

        var OldHtml = document.getElementById(TargetId).innerHTML;
        document.getElementById(TargetId).innerHTML = OldHtml + Response;

    });
};

Xa.Redirect = function(Page) {

    if (Page === undefined) {
        //window.location.href =XaApp.Config.url;
    } else {
        //window.location.href =XaApp.Config.url+Page;
    }
};