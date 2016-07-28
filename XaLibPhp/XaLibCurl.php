<?php

class XaLibCurl {

    public static function CallUrl ($url) {

        $ch = curl_init();

        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);

        $response = curl_exec($ch);
        curl_close($ch);	
        
        return $response;
    }

	public static function CallPost (&$url,&$FieldsString,$ResponseType,array &$Conf) {
        $ch = curl_init();

        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
        curl_setopt($ch, CURLOPT_POST,1);
        curl_setopt($ch, CURLOPT_POSTFIELDS, $FieldsString);

        $response = curl_exec($ch);
        curl_close($ch);

        if($ResponseType=="Array") {
            
            return XaLibCurl::GetCurlResAsArray($response,$Conf);

        } else if ($ResponseType=="json") {

        return XaLibCurl::GetCurlResAsJson($response,$Conf);

        } else {
            
            return $response;
        }

    }

      private static function GetCurlResAsJson(&$Response,array &$Conf) {

        libxml_use_internal_errors(true);

        if (!simplexml_load_string($Response) ){

            //CHECK LOW LEVEL SYSTEM ERROR
            echo $Response;
            exit();

        } else {

            $xml = simplexml_load_string($Response);
            $json= str_replace('{}','""',json_encode($xml));
            $WsData = json_decode($json,TRUE);

            XaLibCurl::CheckApiError($WsData,$Conf);

            return $json;
        }
    }
    
    private static function GetCurlResAsArray(&$Response,array &$Conf) {

        libxml_use_internal_errors(true);

        if (!simplexml_load_string($Response) ){

            //CHECK LOW LEVEL SYSTEM ERROR
            echo $Response;
            exit();

        } else {

            $xml = simplexml_load_string($Response);
            $json= str_replace('{}','""',json_encode($xml));
            $WsData = json_decode($json,TRUE);

            XaLibCurl::CheckApiError($WsData,$Conf);

            return $WsData;
        }
    }
    
    private static function CheckApiError(array $ApiResponse,array &$Conf) {

        if(array_key_exists("error",$ApiResponse)){

            // $ApiResponse['error']['number']=="52"
            if ($ApiResponse['error']['number']=="45" ) {

                XaLibUtils::Redirect($Conf["MyApp"]["LoginPage"]."?Error=45");
                
            }

            if ($ApiResponse['error']['number']=="52" ) {

                XaLibUtils::Redirect($Conf["MyApp"]["LoginPage"]."?Error=52");

            }

            echo $ApiResponse['error']['number'];
            echo $ApiResponse['error']['description'];

        exit();
            
        }
    }

}
?>