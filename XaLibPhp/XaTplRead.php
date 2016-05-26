<?php

require_once('XaTpl.php');

/**
 * Description of XaLibApi
 *
 * @author alex
 */

class XaTplRead extends XaTpl{

    function __construct() {
        
    }

    public function Read(array $Conf,XaLibHttp &$HTTP,array &$WsData):string {

        $Content='<ul class="form form-1-column">';

        foreach($WsData['read'] as $key => $value) {
			$Content.='<li>'.$key.'</li>';
            $Content.='<li>'.$value.'</li>';
        }
		$Content.="<li/>";
        $Content.="</ul>";

		return $Content;

    }
}
?>