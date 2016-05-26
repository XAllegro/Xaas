<?php

class XaLibCurl {

    public static function CallGet (&$url) {

        $ch = curl_init();

        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);

        $response = curl_exec($ch);
        curl_close($ch);	

        return $response;
    }

    public static function CallPost (&$url,&$FieldsString,$ResponseType) {

        $ch = curl_init();

        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
        curl_setopt($ch,CURLOPT_POST,1);
        curl_setopt($ch,CURLOPT_POSTFIELDS, $FieldsString);

        $response = curl_exec($ch);
        curl_close($ch);

        if($ResponseType=="Array") {

            return XaLibCurl::GetCurlResAsArray($response);

        } else {
            return $response;
        }

    }

    private static function GetCurlResAsArray(&$Response) {

        libxml_use_internal_errors(true);

        if (!simplexml_load_string($Response) ){

            //CHECK LOW LEVEL SYSTEM ERROR
            echo $Response;
            exit();

        } else {

            $xml = simplexml_load_string($Response);
            $json= str_replace('{}','""',json_encode($xml));
            $WsData = json_decode($json,TRUE);

            XaLibCurl::CheckApiError($WsData);
            
            return $WsData;
        }
    }
    
    
    private static function CheckApiError(array $ApiResponse) {

        if(array_key_exists("error",$ApiResponse)){
            
            echo $ApiResponse['error']['number'];
            echo $ApiResponse['error']['description'];

        exit();
            
        }
    }
}
?>