<html>
<head>
	<meta http-equiv="refresh" content="3">
</head>
<body>
<h3>Interactive Device Design Chat</h3>
<pre>
<?php
 $chat = file_get_contents('./chat.txt');
 echo htmlspecialchars($chat);
?>	
</pre>
</body>

</html>