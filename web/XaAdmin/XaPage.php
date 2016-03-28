<?php

    require_once ('XaConf.php');

    /**
     *
     * Pages Controller
     * @example XaPage.php?obj=XaUser&evt=List&lay=Explorer&type=actions
     * 
     * @author alessandro mariotti
     * @author alex@xallegro.com
     */

    /*CHECK LOGIN*/

    //$lay="Standalone";
    if ($HTTP->ExistsHttpParam("lay")) {

        $lay=$HTTP->GetHttpParam('lay');
        
        /*SELECT THE LAYOUT*/
        $LayoutToInclude="XaPage".$lay.".php";
        
        require_once ($LayoutToInclude);
    }
?>