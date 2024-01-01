<?php
$server = 'localhost';
$user = 'xiaoming'; //用户名
$password = '123456';//密码
$dbname = 'test';//数据库名

$conn = mysqli_connect($server, $user, $password, $dbname);

if (!$conn) {
    die("连接失败" . mysqli_connect_error());
}
$uid = $_REQUEST['id'];
// 字符型
$sql = "select id,lastname,email from class where id='" . $uid . "'";

$result = mysqli_query($conn, $sql);
if (isset($uid) && $uid != '') {
    if (mysqli_num_rows($result) > 0) {
        $html .=  "<table>";
        while ($row = mysqli_fetch_array($result)) {
            $id = $row['id'];
            $name = $row['lastname'];
            $email = $row['email'];
            $html .= "<tr><td>id:{$id}</td><td>name:{$name}</td><td>email:{$email}<td></td>";
        }
        $html .=  "</table>";
    } else {

        $html .=  "<p>你输入的userID不存在,请重新输入!</p>";
    }
} else {
    $html .= "请在输入框输入数字!<br>";
}
$html .= "你输入的sql语句是:{$sql}";

mysqli_close($conn);

?>
<html>
<body>
    <h1>第一关：联合查询注入/布尔注入</h1>
    <form action="" method="get">
        <input name="id" value="">
        <input name="submit" value="submit" type="submit">
    </form>
    <?php echo $html; ?>
</body>

</html>
