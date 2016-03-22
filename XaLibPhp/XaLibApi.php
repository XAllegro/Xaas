<?php

require_once('XaLibCurl.php');
/**
 * Description of XaLibApi
 *
 * @author alex
 */

class XaLibApi {

    protected final function GetBaseUrl(array &$Conf,string $ApiName):string {

        $BaseUrl=$Conf[$ApiName]["Protocol"]."://".$Conf[$ApiName]["ApiUrl"]."?";
        $BaseUrl.="ReqType=".$Conf[$ApiName]["ReqType"];
        $BaseUrl.="&Encoding=".$Conf[$ApiName]["Encoding"];
        $BaseUrl.="&Encryption=".$Conf[$ApiName]["Encryption"];
        $BaseUrl.="&ResType=".$Conf[$ApiName]["ResType"];
        $BaseUrl.="&ConsumerId=".$Conf[$ApiName]["ConsumerId"];
        return $BaseUrl;
    }

    protected final function Redirect(string $page) {
        header( 'Location: '.$page ) ;

    }
    
    protected final function CheckApiError(array $ApiResponse) {

        if ($ApiResponse['error']['number']) {
            
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
                    if (validate_ip($ip))
                        return $ip;
                }
            } else {
                if (validate_ip($_SERVER['HTTP_X_FORWARDED_FOR']))
                    return $_SERVER['HTTP_X_FORWARDED_FOR'];
            }
        }
        if (!empty($_SERVER['HTTP_X_FORWARDED']))
            return $_SERVER['HTTP_X_FORWARDED'];
        if (!empty($_SERVER['HTTP_X_CLUSTER_CLIENT_IP']) )
            return $_SERVER['HTTP_X_CLUSTER_CLIENT_IP'];
        if (!empty($_SERVER['HTTP_FORWARDED_FOR']))
            return $_SERVER['HTTP_FORWARDED_FOR'];
        if (!empty($_SERVER['HTTP_FORWARDED']))
            return $_SERVER['HTTP_FORWARDED'];

        // return unreliable ip since all else failed
        return $_SERVER['REMOTE_ADDR'];
    }

/*COMMON API CALLS*/

    public function RearrangeListResultArray(array &$WsData) {
	// When the list results contain a single <item> node, the 'item' level
	// is missing from the array and must be added

        if (count($WsData['list'])==0) {
            // empty list, do nothing
        } else if (isset($WsData['list']['item'][0])) {
            // multiple items, do nothing
        } else {
            // single item, correction
            $WsData['list']['item']=Array($WsData['list']['item']);
       }
    }

    public function List(array &$Conf,XaLibHttp &$HTTP):array {

        if ($HTTP->CookieGet("XaSessionId")!="") {

            $url=$this->GetBaseUrl($Conf,$HTTP->GetHttpParam("obj"))."&Data=<WsData>";
            $url.="<login><client_ip>".$this->GetIpAddress()."</client_ip><token>".$HTTP->CookieGet("XaSessionId")."</token></login>";
            $url.="<operation><object>".$HTTP->GetHttpParam("obj")."</object><event>List</event></operation>";
            $url.="<params><p><n></n><v></v></p></params>";
            $url.="</WsData>";

            $xml = simplexml_load_string(XaLibCurl::CallUrl($url));
            $json = json_encode($xml);
            $WsData = json_decode($json,TRUE);
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
            $url.="<login><client_ip>".$this->GetIpAddress()."</client_ip><token>".$HTTP->CookieGet("XaSessionId")."</token></login>";
            $url.="<operation><object>".$HTTP->GetHttpParam("obj")."</object><event>Read</event></operation>";
            $url.="<params><p><n>id</n><v>".$HTTP->GetHttpParam("id")."</v></p></params>";
            $url.="</WsData>";

            $xml = simplexml_load_string(XaLibCurl::CallUrl($url));
            $json = json_encode($xml);
            $WsData = json_decode($json,TRUE);
            return $WsData;
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
        } else {
            //MANDARE LOGIN
        }
    }

    public function ListWithKey(array &$Conf,XaLibHttp &$HTTP,string $Obj,string $KeyName,string $KeyValue):array {

        if ($HTTP->CookieGet("XaSessionId")!="") {

            $url=$this->GetBaseUrl($Conf,$Obj)."&Data=<WsData>";
            $url.="<login><client_ip>".$this->GetIpAddress()."</client_ip><token>".$HTTP->CookieGet("XaSessionId")."</token></login>";
            $url.="<operation><object>".$Obj."</object><event>List</event></operation>";
            $url.="<params><p><n>".$KeyName."</n><v>".$KeyValue."</v></p></params>";
            $url.="</WsData>";

            $xml = simplexml_load_string(XaLibCurl::CallUrl($url));
            $json = json_encode($xml);
            $WsData = json_decode($json,TRUE);
            $this->RearrangeListResultArray($WsData);

            return $WsData;
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
        } else {
            //MANDARE LOGIN
        }
    }

    public function CreateFrm(array &$Conf,XaLibHttp &$HTTP):array {

        if ($HTTP->CookieGet("XaSessionId")!="") {
            $url=$this->GetBaseUrl($Conf,$HTTP->GetHttpParam("obj"))."&Data=<WsData>";
            $url.="<login><client_ip>".$this->GetIpAddress()."</client_ip><token>".$HTTP->CookieGet("XaSessionId")."</token></login>";
            $url.="<operation><object>".$HTTP->GetHttpParam("obj")."</object><event>GetXmlModel</event></operation>";
            $url.="<params><p><n></n><v></v></p></params>";
            $url.="</WsData>";

            $xml = simplexml_load_string(XaLibCurl::CallUrl($url));
            $json = json_encode($xml);
            $WsData = json_decode($json,TRUE);
            return $WsData;
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);

        } else {
            //MANDARE LOGIN
        }
    }

}
?>