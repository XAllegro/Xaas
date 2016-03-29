<?php

require_once('XaLibCurl.php');
/**
 * Description of XaLibApi
 *
 * @author alex
 */

class XaLibApi {

    protected $_obj="";

    protected final function GetBaseUrl(array &$Conf,$ApiName):string {

        $BaseUrl=$Conf[$ApiName]["Protocol"]."://".$Conf[$ApiName]["ApiUrl"]."?";
        $BaseUrl.="ReqType=".$Conf[$ApiName]["ReqType"];
        $BaseUrl.="&Encoding=".$Conf[$ApiName]["Encoding"];
        $BaseUrl.="&Encryption=".$Conf[$ApiName]["Encryption"];
        $BaseUrl.="&ResType=".$Conf[$ApiName]["ResType"];
        $BaseUrl.="&ConsumerId=".$Conf[$ApiName]["ConsumerId"];
        return $BaseUrl;
    }
    
    protected final function GetLoginSection(XaLibHttp &$HTTP):string {

        $section="<login><client_ip>".$this->GetIpAddress()."</client_ip><token>".$HTTP->CookieGet("XaSessionId")."</token></login>";

        return $section;
    }

    protected final function ClearParamValue($v):string {

        $v=rawurlencode($v);
        // clear for xml
        $v=str_replace('%26','%2526',$v);	// & -> %26 -> %2526
        $v=str_replace('%3C','%253C',$v);	// < -> %3C -> %253C
        $v=str_replace('%3E','%253E',$v);	// > -> %3E -> %253E
        // ' " yet to be cleared

        return $v;
    }
    
    protected final function GetCurlResAsArray($url):array {

            $xml = simplexml_load_string(XaLibCurl::CallUrl($url));
            $json = json_encode($xml);
            $json= str_replace('{}','""',$json);
            $WsData = json_decode($json,TRUE);
            return $WsData;
    } 
    
    protected final function Redirect($page) {
        header( 'Location: '.$page ) ;

    }

    protected final function CheckApiError(array $ApiResponse) {

        if(array_key_exists("error",$ApiResponse)){
        
            //if ($ApiResponse['error']['number']) {
            
            echo $ApiResponse['error']['number'];
            echo $ApiResponse['error']['description'];
            
            //Change with an ErrorPage
        exit();
            
        }
    }

    protected final function GetIpAddress():string {

        if (!empty($_SERVER['HTTP_CLIENT_IP'])) {
            return $_SERVER['HTTP_CLIENT_IP'];
        }

        if (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) {

            if (strpos($_SERVER['HTTP_X_FORWARDED_FOR'], ',') !== false) {
                $iplist = explode(',', $_SERVER['HTTP_X_FORWARDED_FOR']);
                foreach ($iplist as $ip) {
                  //  if (validate_ip($ip))       
                  return $ip;
                }
            } else {
                //if (validate_ip($_SERVER['HTTP_X_FORWARDED_FOR']))
                    return $_SERVER['HTTP_X_FORWARDED_FOR'];
                //}
            }

        if (!empty($_SERVER['HTTP_X_FORWARDED']))
            return $_SERVER['HTTP_X_FORWARDED'];
        if (!empty($_SERVER['HTTP_X_CLUSTER_CLIENT_IP']) )
            return $_SERVER['HTTP_X_CLUSTER_CLIENT_IP'];
        if (!empty($_SERVER['HTTP_FORWARDED_FOR']))
            return $_SERVER['HTTP_FORWARDED_FOR'];
        if (!empty($_SERVER['HTTP_FORWARDED']))
            return $_SERVER['HTTP_FORWARDED'];

        }
        // return unreliable ip since all else failed
        return $_SERVER['REMOTE_ADDR'];

    }
    
    protected function RearrangeListResultArray(array &$WsData) {
	// When the list results contain a single <item> node, the 'item' level
	// is missing from the array and must be added

        if (!isset($WsData['list']['item'])) {
            // empty list, add empty array of items
            $WsData['list']['item']=Array();
        } else if (isset($WsData['list']['item'][0])) {
            // multiple items, do nothing
        } else {
            // single item, correction with array in the middle
            $WsData['list']['item']=Array($WsData['list']['item']);
       }
    }

    public function GetXmlModel(array &$Conf,XaLibHttp &$HTTP):array {
    
        if ($HTTP->CookieGet("XaSessionId")!="") {
            $url=$this->GetBaseUrl($Conf,$HTTP->GetHttpParam("obj"))."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$HTTP->GetHttpParam("obj")."</object><event>GetXmlModel</event></operation>";
            $url.="<params><p><n></n><v></v></p></params>";
            $url.="</WsData>";
    
            return $this->GetCurlResAsArray($url);
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
    
        } else {
            
            //MANAGE ERROR
        }
    }

    public function Create(array &$Conf,XaLibHttp &$HTTP):array {
    
        if ($HTTP->CookieGet("XaSessionId")!="") {
    
            $url=$this->GetBaseUrl($Conf,$HTTP->GetHttpParam("obj"))."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$HTTP->GetHttpParam("obj")."</object><event>Create</event></operation>";
            $url.="<params>";
            foreach($_GET as $n=>$v) {
                if ($n!='obj' && $n!='evt') {
                    $url.="<p><n>".$n."</n><v>".$this->ClearParamValue($v)."</v></p>";
                }
            }
            $url.="</params>";
            $url.="</WsData>";
    
            $WsData= $this->GetCurlResAsArray($url);
    
            echo($WsData['create']);
            return $WsData;
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
    
        } else {
            //MANDARE LOGIN
        }
    }

    public function List(array &$Conf,XaLibHttp &$HTTP):array {

        if($HTTP->ExistsHttpParam("obj")) {

            $object=$HTTP->GetHttpParam("obj");
        } else {
            
            $object=$this->_obj;
        }
        
        if ($HTTP->CookieGet("XaSessionId")!="") {

            $url=$this->GetBaseUrl($Conf,$object)."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$object."</object><event>List</event></operation>";
            $url.="<params><p><n></n><v></v></p></params>";
            $url.="</WsData>";
            
            $WsData=$this->GetCurlResAsArray($url); 
            $this->RearrangeListResultArray($WsData);

            return $WsData;
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
        } else {
            //MANDARE LOGIN
        }
    }

    public function ListAsOptions(array &$Conf,XaLibHttp &$HTTP,$Obj=""):array {

        if ($Obj=="") {

            $Obj=$HTTP->GetHttpParam("obj");
        }

        if ($HTTP->CookieGet("XaSessionId")!="") {
    
            $url=$this->GetBaseUrl($Conf,$Obj)."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$Obj."</object><event>ListAsOptions</event></operation>";
            $url.="<params><p><n></n><v></v></p></params>";
            $url.="</WsData>";
    
            $WsData = $this->GetCurlResAsArray($url);
            $this->RearrangeListResultArray($WsData);
    
            return $WsData;
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
        } else {
            //MANDARE LOGIN
        }
    }

    public function Read(array &$Conf,XaLibHttp &$HTTP):array {

        if ($HTTP->CookieGet("XaSessionId")!="") {

            $url=$this->GetBaseUrl($Conf,$HTTP->GetHttpParam("obj"))."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP); 
            $url.="<operation><object>".$HTTP->GetHttpParam("obj")."</object><event>Read</event></operation>";
            $url.="<params><p><n>id</n><v>".$HTTP->GetHttpParam("id")."</v></p></params>";
            $url.="</WsData>";

            return $this->GetCurlResAsArray($url);
            
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
        } else {
            //MANDARE LOGIN
        }
    }

    public function ListByUser(array &$Conf,XaLibHttp &$HTTP):array {

        if($HTTP->ExistsHttpParam("obj")) {
            
            $object=$HTTP->GetHttpParam("obj");
        } else {
            
            $object=$this->_obj;
        }
        
        if ($HTTP->CookieGet("XaSessionId")!="") {

            $url=$this->GetBaseUrl($Conf,$object)."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$object."</object><event>ListByUser</event></operation>";
            $url.="<params><p><n>XaUser_ID</n><v>".$HTTP->GetHttpParam("XaUser_ID")."</v></p></params>";
            $url.="</WsData>";

            $WsData=$this->GetCurlResAsArray($url);
 
            $this->RearrangeListResultArray($WsData);
            return $WsData;
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
        } else {
            //MANDARE LOGIN
        }
    }

    
    
    

    
    
    
    public function ListWithKey(array &$Conf,XaLibHttp &$HTTP,$Obj,$KeyName,$KeyValue):array {

        if ($HTTP->CookieGet("XaSessionId")!="") {

            $url=$this->GetBaseUrl($Conf,$Obj)."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$Obj."</object><event>List</event></operation>";
            $url.="<params><p><n>".$KeyName."</n><v>".$KeyValue."</v></p></params>";
            $url.="</WsData>";

            $WsData =$this->GetCurlResAsArray($url);

            $this->RearrangeListResultArray($WsData);

            return $WsData;
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
        } else {
            //MANDARE LOGIN
        }
    }
    
    public function ListWithKeyArray(array &$Conf,XaLibHttp &$HTTP,$Obj,array $KeyName,array $KeyValue):array {

        if ($HTTP->CookieGet("XaSessionId")!="") {

            $url=$this->GetBaseUrl($Conf,$Obj)."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$Obj."</object><event>List</event></operation>";
            $url.="<params>";
            
            for ($i = 0; $i < count($KeyName); $i++) {
              $url.="<p><n>".$KeyName[$i]."</n><v>".$KeyValue[$i]."</v></p>";
            }
            
            $url.="</params>";
            $url.="</WsData>";

            $WsData =  $this->GetCurlResAsArray($url);
            $this->RearrangeListResultArray($WsData);

            return $WsData;
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
        } else {
            //MANDARE LOGIN
        }
    }
/*
    public function CreateFrm(array &$Conf,XaLibHttp &$HTTP):array {

        if ($HTTP->CookieGet("XaSessionId")!="") {
            $url=$this->GetBaseUrl($Conf,$HTTP->GetHttpParam("obj"))."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$HTTP->GetHttpParam("obj")."</object><event>GetXmlModel</event></operation>";
            $url.="<params><p><n></n><v></v></p></params>";
            $url.="</WsData>";
            
            return $this->GetCurlResAsArray($url);;
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);

        } else {
            //MANDARE LOGIN
        }
    }
*/
    public function UpdateFrm(array &$Conf,XaLibHttp &$HTTP):array {

        if ($HTTP->CookieGet("XaSessionId")!="") {
            // model
            $url=$this->GetBaseUrl($Conf,$HTTP->GetHttpParam("obj"))."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$HTTP->GetHttpParam("obj")."</object><event>GetXmlModel</event></operation>";
            $url.="<params><p><n></n><v></v></p></params>";
            $url.="</WsData>";

            $xml = simplexml_load_string(XaLibCurl::CallUrl($url));
            $json = json_encode($xml);
            $WsModel = json_decode($json,TRUE);

            // data
            $url=$this->GetBaseUrl($Conf,$HTTP->GetHttpParam("obj"))."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$HTTP->GetHttpParam("obj")."</object><event>ReadForUpdateFrm</event></operation>";
            $url.="<params><p><n>id</n><v>".$HTTP->GetHttpParam("id")."</v></p></params>";
            $url.="</WsData>";

            $WsData =  $this->GetCurlResAsArray($url);

            return array($WsModel,$WsData);
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);

        } else {
            //MANDARE LOGIN
        }
    }

    public function Update(array &$Conf,XaLibHttp &$HTTP):array {

        if ($HTTP->CookieGet("XaSessionId")!="") {

            $url=$this->GetBaseUrl($Conf,$HTTP->GetHttpParam("obj"))."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$HTTP->GetHttpParam("obj")."</object><event>Update</event></operation>";
            $url.="<params>";
            foreach($_GET as $n=>$v) {
                if ($n!='obj' && $n!='evt') {
                  $url.="<p><n>".$n."</n><v>".$v."</v></p>";
                }
            }

            $url.="</params>";
            $url.="</WsData>";

            
            $WsData = $this->GetCurlResAsArray($url);

echo($WsData['update']);
            return $WsData;
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
        } else {
            //MANDARE LOGIN
        }
    }


   

    public function Delete(array &$Conf,XaLibHttp &$HTTP):array {

        if ($HTTP->CookieGet("XaSessionId")!="") {

            $url=$this->GetBaseUrl($Conf,$HTTP->GetHttpParam("obj"))."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$HTTP->GetHttpParam("obj")."</object><event>Delete</event></operation>";
            $url.="<params><p><n>id</n><v>".$HTTP->GetHttpParam("id")."</v></p></params>";
            $url.="</WsData>";

            $WsData = $this->GetCurlResAsArray($url);

echo($WsData['delete']);
            return $WsData;
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
        } else {
            //MANDARE LOGIN
        }
    }

}
?>