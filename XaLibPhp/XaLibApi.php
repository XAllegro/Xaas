<?php

require_once('XaLibCurl.php');
/**
 * Description of XaLibApi
 *
 * @author alex
 */


class XaLibApi {
    
    //protected $BackEndRes;

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

}

?>