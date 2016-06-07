<?php

require_once('XaLibCurl.php');
require_once('XaLibUtils.php');
/**
 * Description of XaLibApi
 *
 * @author alex
 */

class XaLibApi {

    public function BackEndCall ($api,$obj,$evt,array &$Conf, XaLibHttp &$HTTP, $ApiParams) {

       
        if($obj=="XaUserLogin" && $evt=="Login") {

            $url=$this->GetBaseUrl($Conf,$api,"XaUserLogin","Login");
            $FieldsString=$HTTP->GetHttpRequestAsString($ApiParams);
            $result=XaLibCurl::CallPost ($url,$FieldsString,"Array");

            if ($result["token"]) {

                $HTTP->CookieSet($result["token"]);
                XaLibUtils::Redirect($Conf["MyApp"]["MyPage"]);
            }
          
        } else if ($obj=="XaUserLogin" && $evt=="Logout") {
    
            $url=$this->GetBaseUrl($Conf,$api,"XaUserLogin","Logout");
            $FieldsString=$HTTP->GetHttpRequestAsString($ApiParams,$HTTP->CookieGet("XaSessionId"));
            $result=XaLibCurl::CallPost ($url,$FieldsString,"Array");

            $HTTP->CookieUnset();
            XaLibUtils::Redirect($Conf["MyApp"]["LogoutPage"]);
            
        } else {

            $url=$this->GetBaseUrl($Conf,$api,$obj,$evt);
            $FieldsString=$HTTP->GetHttpRequestAsString($ApiParams,$HTTP->CookieGet("XaSessionId"));
            $result=XaLibCurl::CallPost ($url,$FieldsString,"Array");
            
            if ($evt=="List" || $evt=="ListAsOptions") {
                
                return $this->CorretArrayDepth($result);
                
            } else {
            
                return $result;
            
            }
        }

    }

    protected final function GetBaseUrl(array &$Conf,$api,$obj,$evt) {

        $BaseUrl=$Conf[$api]["Protocol"]."://".$Conf[$api]["ApiUrl"]/*."?"*/;
        
        if ($obj!="" && $evt!="") {
            
            $BaseUrl.="/?obj=".$obj."&evt=".$evt;
            
        }
        
        
        return $BaseUrl;
    }
    
    protected final function CorretArrayDepth(array $WsData) {

        if(isset($WsData['list']['item'])) {

            if (isset($WsData['list']['item'][0])) {

                } else {
                    $TempWsdata=$WsData['list']['item'];
                    $NewWsData = array( "list" => array( "item"=>array($TempWsdata)));
                    $WsData=$NewWsData;
                }

            } else {

                 $NewWsData = array( "list" => array( "item"=>array("no_data")));
                 $WsData=$NewWsData;
            }
        
        return $WsData;
    }
    
/*
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

    protected function GetXmlModel(array &$Conf,XaLibHttp &$HTTP):array {

        $this->GetParams($HTTP);

        $url=$this->GetBaseUrl($Conf,$this->object)."&Data=<WsData>";
        $url.=$this->GetLoginSection($HTTP);
        $url.="<operation><object>".$this->object."</object><event>GetXmlModel</event></operation>";
        $url.= $this->GetParamsSection($this->params);
        $url.="</WsData>";

        $WsData=$this->GetCurlResAsArray($url);

        $this->CheckApiError($WsData);

        return $WsData;

    }
*/
/*
    public function Create(array &$Conf,XaLibHttp &$HTTP):array {

        $this->GetParams($HTTP);

        if ($HTTP->CookieGet("XaSessionId")!="") {

            $url=$this->GetBaseUrl($Conf,$this->object)."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP); 
            $url.="<operation><object>".$this->object."</object><event>Create</event></operation>";
            $url.= $this->GetParamsSection($this->params);
            $url.="</WsData>";

            return $this->GetCurlResAsArray($url);
            
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
        } else {
            //MANDARE LOGIN
        }
    }


	public function Create(array &$Conf,XaLibHttp &$HTTP):array {
    
        $url=$this->GetBaseUrl($Conf,$HTTP->GetHttpParam("obj"))."&Data=<WsData>";
        $url.=$this->GetLoginSection($HTTP);
        $url.="<operation><object>".$HTTP->GetHttpParam("obj")."</object><event>Create</event></operation>";
        $url.="<params>";

        //LIST FROM MODEL
        foreach($HTTP->GetHttpRequest() as $n=>$v) {

            if ($n!='obj' && $n!='evt') {
                $url.="<p><n>".$n."</n><v>".$this->ClearParamValue($v)."</v></p>";
            }
        }

        $url.="</params>";
        $url.="</WsData>";
        $WsData= $this->GetCurlResAsArray($url);

        //echo($WsData['create']);
        //return $WsData['create'];
        return $WsData;
        //GESTIRE CASO XML O JSON
        //$this->CheckApiError($result);
    }

    public function List(array &$Conf,XaLibHttp &$HTTP):array {

        $this->GetParams($HTTP);

        if ($HTTP->CookieGet("XaSessionId")!="") {

            $url=$this->GetBaseUrl($Conf,$this->object)."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$this->object."</object><event>List</event></operation>";
            $url.= $this->GetParamsSection($this->params);
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

          $this->GetParams($HTTP);

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

    public function ListAsOptionsDomain(array &$Conf,XaLibHttp &$HTTP,$Obj="",$domain,$tree_parent_ID=""):array {

        $this->GetParams($HTTP);
         
        if ($HTTP->CookieGet("XaSessionId")!="") {
    
            $url=$this->GetBaseUrl($Conf,$Obj)."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$Obj."</object><event>ListAsOptions</event></operation>";
            $url.="<params>";
            $url.="<p><n>domain</n><v>".$domain."</v></p>";
            $url.="<p><n>tree_parent_ID</n><v>".$tree_parent_ID."</v></p>";
            $url.="<p><n></n><v></v></p>";
            $url.="</params>";
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

        $this->GetParams($HTTP);

        if ($HTTP->CookieGet("XaSessionId")!="") {

            $url=$this->GetBaseUrl($Conf,$this->object)."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP); 
            $url.="<operation><object>".$this->object."</object><event>Read</event></operation>";
            $url.= $this->GetParamsSection($this->params);
            $url.="</WsData>";

            return $this->GetCurlResAsArray($url);
            
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
        } else {
            //MANDARE LOGIN
        }
    }

	public function View(array &$Conf,XaLibHttp &$HTTP):array {

        $this->GetParams($HTTP);

        if ($HTTP->CookieGet("XaSessionId")!="") {

            $url=$this->GetBaseUrl($Conf,$this->object)."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP); 
            $url.="<operation><object>".$this->object."</object><event>View</event></operation>";
            $url.= $this->GetParamsSection($this->params);
            $url.="</WsData>";

            return $this->GetCurlResAsArray($url);
            
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
        } else {
            //MANDARE LOGIN
        }
    }

    protected function ListByUser(array &$Conf,XaLibHttp &$HTTP):array {

        $this->GetParams($HTTP);

            $url=$this->GetBaseUrl($Conf,$this->object)."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$this->object."</object><event>ListByUser</event></operation>";
            $url.= $this->GetParamsSection($this->params);
            $url.="</WsData>";

            $WsData=$this->GetCurlResAsArray($url);
 
            $this->RearrangeListResultArray($WsData);
            $this->CheckApiError($WsData);

            return $WsData;
    }
    
    protected function ListByParams(array &$Conf,XaLibHttp &$HTTP):array {

        $this->GetParams($HTTP);

            $url=$this->GetBaseUrl($Conf,$this->object)."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$this->object."</object><event>ListByParams</event></operation>";
            $url.= $this->GetParamsSection($this->params);
            $url.="</WsData>";

            $WsData=$this->GetCurlResAsArray($url);
 
            $this->RearrangeListResultArray($WsData);
            return $WsData;
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
    }
    
    public function ListByIdArray(array &$Conf,XaLibHttp &$HTTP,$Obj,$KeyName,$KeyValue):array {
  
      if ($HTTP->CookieGet("XaSessionId")!="") {
  
        $url=$this->GetBaseUrl($Conf,$Obj)."&Data=<WsData>";
        $url.=$this->GetLoginSection($HTTP);
        $url.="<operation><object>".$Obj."</object><event>ListByIdArray</event></operation>";
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

    public function Update(array &$Conf,XaLibHttp &$HTTP):array {

        if ($HTTP->CookieGet("XaSessionId")!="") {

            $url=$this->GetBaseUrl($Conf,$HTTP->GetHttpParam("obj"))."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$HTTP->GetHttpParam("obj")."</object><event>Update</event></operation>";
            $url.="<params>";
            foreach($HTTP->GetHttpRequest() as $n=>$v) {
                if ($n!='obj' && $n!='evt') {
                  $url.="<p><n>".$n."</n><v>".$this->ClearParamValue($v)."</v></p>";
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

/*
	public function Update(array &$Conf,XaLibHttp &$HTTP):array {

        $this->GetParams($HTTP);

        if ($HTTP->CookieGet("XaSessionId")!="") {

            $url=$this->GetBaseUrl($Conf,$this->object)."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP); 
            $url.="<operation><object>".$this->object."</object><event>Update</event></operation>";
            $url.= $this->GetParamsSection($this->params);
            $url.="</WsData>";

            return $this->GetCurlResAsArray($url);
            
            //GESTIRE CASO XML O JSON
            //$this->CheckApiError($result);
        } else {
            //MANDARE LOGIN
        }
    }


    public function Delete(array &$Conf,XaLibHttp &$HTTP):array {

            $url=$this->GetBaseUrl($Conf,$HTTP->GetHttpParam("obj"))."&Data=<WsData>";
            $url.=$this->GetLoginSection($HTTP);
            $url.="<operation><object>".$HTTP->GetHttpParam("obj")."</object><event>Delete</event></operation>";
            $url.="<params><p><n>id</n><v>".$HTTP->GetHttpParam("id")."</v></p></params>";
            $url.="</WsData>";

            $WsData = $this->GetCurlResAsArray($url);
            $this->CheckApiError($WsData);

            //echo($WsData['delete']);

            return $WsData;
            //GESTIRE CASO XML O JSON

    }

    public function Search(array &$Conf,XaLibHttp &$HTTP,$Obj,array $KeyName,array $KeyValue):array {

        $url=$this->GetBaseUrl($Conf,$Obj)."&Data=<WsData>";
        $url.=$this->GetLoginSection($HTTP);
        $url.="<operation><object>".$Obj."</object><event>Search</event></operation>";
        $url.="<params>";
        
        for ($i = 0; $i < count($KeyName); $i++) {
          $url.="<p><n>".$KeyName[$i]."</n><v>".$KeyValue[$i]."</v></p>";
        }
        
        $url.="</params>";
        $url.="</WsData>";


        $WsData =  $this->GetCurlResAsArray($url);
        $this->RearrangeListResultArray($WsData);

        return $WsData;
    }
    
    public function Portfolio(array &$Conf,XaLibHttp &$HTTP,$Obj,array $KeyName,array $KeyValue):array {

        $url=$this->GetBaseUrl($Conf,$Obj)."&Data=<WsData>";
        $url.=$this->GetLoginSection($HTTP);
        $url.="<operation><object>".$Obj."</object><event>Portfolio</event></operation>";
        $url.="<params>";
        
        for ($i = 0; $i < count($KeyName); $i++) {
          $url.="<p><n>".$KeyName[$i]."</n><v>".$KeyValue[$i]."</v></p>";
        }
        
        $url.="</params>";
        $url.="</WsData>";


        $WsData =  $this->GetCurlResAsArray($url);
        $this->RearrangeListResultArray($WsData['portfolio']);

        return $WsData;
    }

    public function Execute (array &$Conf,XaLibHttp &$HTTP,$evt) {
    
        $this->$evt($Conf,$HTTP);
    }

    public function ExecuteSync (array &$Conf,XaLibHttp &$HTTP,$evt,$obj,$ApiParams) {
    
        $this->_obj=$obj;
        $this->_params=$ApiParams;
    
        return ($this->$evt($Conf,$HTTP));
    }

    public function ExecuteBack (array &$Conf,XaLibHttp &$HTTP,$evt,$key) {

        $Res=$this->$evt($Conf,$HTTP);
        return $Res[$key];
    }

    protected function Universal(array &$Conf,XaLibHttp &$HTTP):array {

        $this->GetParams($HTTP);
		$ParamsArray=json_decode($this->params, true);

        $url=$this->GetBaseUrl($Conf,$this->object)."&Data=<WsData>";
        $url.=$this->GetLoginSection($HTTP);
        $url.="<operation><object>".$this->object."</object>";
		$url.="<event>".$ParamsArray['event']."</event></operation>";
		// 'event' parameter is also included automatically in the <params> section, with no side effect
        $url.= $this->GetParamsSection($this->params);
        $url.="</WsData>";

        $WsData=$this->GetCurlResAsArray($url);

        $this->CheckApiError($WsData);

        return $WsData;

    }

	public function FormUniversal(array &$Conf,XaLibHttp &$HTTP):array {

        $url=$this->GetBaseUrl($Conf,$HTTP->GetHttpParam("obj"))."&Data=<WsData>";
        $url.=$this->GetLoginSection($HTTP);
        $url.="<operation><object>".$HTTP->GetHttpParam("obj")."</object>";
		$url.="<event>".$HTTP->GetHttpParam("event")."</event></operation>";

		// 'event' parameter is also included automatically in the <params> section, with no side effect
        $url.="<params>";

        //LIST FROM MODEL
        foreach($HTTP->GetHttpRequest() as $n=>$v) {
            if ($n!='obj' && $n!='evt') {
                $url.="<p><n>".$n."</n><v>".$this->ClearParamValue($v)."</v></p>";
            }
        }

        $url.="</params>";
        $url.="</WsData>";
        $WsData= $this->GetCurlResAsArray($url);

        //echo($WsData['create']);
        //return $WsData['create'];
        return $WsData;
        //GESTIRE CASO XML O JSON
        //$this->CheckApiError($result);
    }
 */

}
?>