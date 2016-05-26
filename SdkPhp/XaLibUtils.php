<?php

require_once('XaLibCurl.php');
/**
 * Description of XaLibApi
 *
 * @author alex
 */

class XaLibUtils {
   
    static public final function GetIpAddress() {

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

    static public final function Redirect($page) {
        header( 'Location: '.$page ) ;

    }
    
    static public final function ClearParamValue($v) {

        $v=rawurlencode($v);
        // clear for xml
        $v=str_replace('%26','%2526',$v);	// & -> %26 -> %2526
        $v=str_replace('%3C','%253C',$v);	// < -> %3C -> %253C
        $v=str_replace('%3E','%253E',$v);	// > -> %3E -> %253E
        // ' " yet to be cleared

        return $v;
    }
    
    
}
?>