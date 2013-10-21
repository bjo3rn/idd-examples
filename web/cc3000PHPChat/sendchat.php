<?php
  if (isset($_GET['msg'])) {
	$line = strval($_SERVER['REMOTE_ADDR'])." at ".date("H:i:s")." said: ".$_GET['msg']."\n";
    if (file_put_contents("./chat.txt",$line,FILE_APPEND|LOCK_EX)) {  
      echo "Received chat message: $line";
    } else {
	  echo "Received chat message but failed to save it.";
	}

  } else {
	echo "Did not receive chat message. Pass as sendchat.php?msg=XYZ";
  }

?>