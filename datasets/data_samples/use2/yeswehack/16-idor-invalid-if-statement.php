<?php

function View($sess, $user, $id) {    
    if ($sess != '4ebdbacd03dc1a3116f62efdd9c58f06df46de3b5d3dce409257ded24f44bb04' && $user != 'tom' ) {
        echo "You are not authorized to view this content.";
        return;
    } 
    $filename = "$id.json";
    readfile("details/$filename");
}

if ( isset($_GET['details'], $_COOKIE['usess'], $_COOKIE['id']) ) {
    $id = intval($_COOKIE['id']);
    $sess = preg_replace('/[^a-zA-Z0-9]/i', '', $_COOKIE['usess']);
    $user = preg_replace('/[^a-zA-Z0-9]/i', '', $_COOKIE['user']);

    echo '<pre style="font-size:16px">',View($sess, $user, $id),'</pre>';
}

?>