<?php
/**
 * Created by PhpStorm.
 * User: Guimin ZHOU
 * Date: 9/16/14
 * Time: 12:47 AM
 */
if(isset($_POST['image']) && !empty($_POST['image']) && isset($_POST['username']) && !empty($_POST['username'])) {
    $image = $_POST['image'];
    $username = $_POST['username'];
    // get the dataURL
    $dataURL = $_POST["image"];

    // the dataURL has a prefix (mimetype+datatype)
    // that we don't want, so strip that prefix off
    $parts = explode(',', $dataURL);
    $data = $parts[1];

    // Decode base64 data, resulting in an image
    $data = base64_decode($data);

    // create a temporary unique file name
    $file = 'C:\xampp\htdocs\FaceRecognitionProject\Images\\'.$username.'.png';
    $cropFile = 'C:\xampp\htdocs\FaceRecognitionProject\Images\\'.$username.'-crop.jpg';
    // write the file to the upload directory
    $success = file_put_contents($file, $data);
    if(0 == fcActivate($activation_key)){

        $context_id = fcCreateContextID();

        if (0 == fcFaceCrop(getcwd().'/'.$file, getcwd().$cropFile, 128, 196, $context_id)){
            echo '<img src="'.$cropFile.'">';
        } else {
            echo "Error cropping face";
        }

        fcFreeContextID($context_id);
    } else {
        echo "Error: can't activate FaceCrop library";
    }
} else {
    echo "Internal Error";
}