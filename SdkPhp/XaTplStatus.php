<?php

/**
 * Description of XaLibApi
 *
 * @author Alessandro Mariotti
 */

class XaTplStatus {

    static final function GetTplStatusForList(array $WsData,$i) {

        $Content="";
        if ($WsData['list']['item'][$i]['status']==0) {
                                            
        $Content.='<td class="StatusUnchangeable"><span>Unchangeable</span></td>';

        } else if ($WsData['list']['item'][$i]['status']==1) {

            $Content.='<td class="StatusActive"><span>Active</span></td>';

        } else if ($WsData['list']['item'][$i]['status']==2) {

            $Content.='<td class="StatusInactive"><span>Inactive</span></td>';

        } else if ($WsData['list']['item'][$i]['status']==3) {

            $Content.='<td class="StatusArchived"><span>Archived</span></td>';

        } else if ($WsData['list']['item'][$i]['status']==4) {

             $Content.='<td class="StatusDeleted"><span>Deleted</span></td>';
        }
        
        return $Content;
    }
    
    
    /* CAMPAIGN STATUS
    1 : Scheduled	 
    2 : OnGoing
    3 : Expired	 
    4 : Paused
    */
    
    static final function GetTplCampaignStatusForList(array $WsData,$i) {

        $Content="";
        if ($WsData['list']['item'][$i]['campaign_status']==1) {

            $Content.='<td class="StatusScheduled"><span>Scheduled</span></td>';

        } else if ($WsData['list']['item'][$i]['campaign_status']==2) {

            $Content.='<td class="StatusOnGoing"><span>On Going</span></td>';

        } else if ($WsData['list']['item'][$i]['campaign_status']==3) {

            $Content.='<td class="StatusExpired"><span>Expired</span></td>';

        } else if ($WsData['list']['item'][$i]['campaign_status']==4) {

             $Content.='<td class="StatusPaused"><span>Paused</span></td>';
        }
        
        return $Content;
    }

}
?>