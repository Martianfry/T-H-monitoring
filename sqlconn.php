<?php
function sqlconn(){
        $connect = mysqli_connect('localhost','mysql_user_id','mysql_user_pw','mysql_database');
        if(!$connect) die('MYSQL : Server Not Connected');
        else return $connect;
}
?>
