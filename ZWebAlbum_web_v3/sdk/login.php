<?php
    /**
     * 用于用户的登录操作
     * @author ZHG <CyberZHG@gmail.com>
     */

    /**
     * 利用用户名和密码登录，通常用于站外登录的情况。
     * 如果是站内的应用通常不必再次使用用户名和密码登录，直接调用getSessionID()即可。
     * @global string $session_id 用于记录会话的ID。
     * @param string $name 用户名
     * @param string $password 密码
     * @return string 如果登录成功会自动设置$session_id的值，无返回值。否则返回字符串说明失败原因。
     */
    function login($name, $password) {
        global $session_id;
    }

    /**
     * 获取会话的ID，自动设置全局变量的值。
     * @global <type> $session_id 用于记录会话的ID。
     * @return string 如果已经登录则可以返回会话的ID，否则返回空字符串。
     */
    function getSessionID() {
        global $session_id;
    }

    /**
     * 删除会话的ID，退出会话。
     * @global string $session_id 用于记录会话的ID。
     */
    function logout() {
        global $session_id;
        $session_id = "";
        $ch = curl_init();
        echo  DOMINE_NAME . "/api/application/application_session.php?apikey=" . API_KEY . "&name=test&password=test";
        curl_setopt($ch, CURLOPT_URL, DOMINE_NAME . "/api/application/application_session.php?apikey=" . API_KEY . "&name=test&password=test");
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($ch, CURLOPT_HEADER, 0);
        $output = curl_exec($ch);
        if($output === FALSE)
        {
            //
        }
        else
        {
            print_r($output);
        }
        curl_close($ch);
    }

?>
