<?php
    if(!isset($_GET["devkey"])){ // devkey in TH_ESP32.ino file
        $returnJSON = json_encode(array('devkey'=>false));
        echo $returnJSON;
    }else{
        $devkey = $_GET["devkey"];
        $reqtime = date('H:i:s',time());
        $reqdate = date('Y-m-d',time());
        if(isset($_GET["date"])){
            $date = $_GET["date"]; // foramt example: 2023-01-01
        }else{
            $date = $reqdate;
        }
        if(isset($_GET["time"])){
            $time = $_GET["time"]; // foramt example: 14:30:00
        }else{
            $time = $reqtime;
        }
        if($devkey=="100"){
            $temp = $_GET["temperature"]; // foramt example: 134.21
            $humd = $_GET["humidity"]; // foramt example: 58.43
            include('sqlconn.php'); $connect = sqlconn();
            $sql = "INSERT INTO YourSQLTable(date, time, temperature, humidity) VALUES(?, ?, ?, ?)";
            $stmt = mysqli_prepare($connect,$sql);
            mysqli_stmt_bind_param($stmt,"ssdd",$date,$time,$temp,$humd);
            mysqli_stmt_execute($stmt);
            $returnJSON = json_encode(array('devkey'=>true,'status'=>true));
            echo $returnJSON;
        }else{
            $returnJSON = json_encode(array('devkey'=>false));
            echo $returnJSON;
        }
    }
?>