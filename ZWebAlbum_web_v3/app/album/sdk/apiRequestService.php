<?php
include_once "apiConfig.php";
include_once "httpRequestService.php";

/**
 * 用于基本的API请求操作。
 * @author ZHG <CyberZHG@gmail.com>
 */
class ApiRequestService extends HttpRequestService {
    /**
     * @var stdClass $api_config 基本的配置信息。
     * @var string $user_token 用户许可的令牌。
     */
    protected $api_config;
    protected $user_token;

    private $token_cookie;

    /**
     * 初始化http请求和基本配置，如果启用了cookie，在获得过令牌后再次创建类的时候则无需再次执行getUserToken操作。
     * @global string $api_config 位于位置文件中的基本配置信息。
     */
    public function  __construct() {
        global $api_config;
        parent::__construct();
        $this->api_config = $api_config;
        $this->user_token = "";
        $this->token_cookie = "token_" . $this->api_config->API_KEY;
        if(isset($_COOKIE[$this->token_cookie])) {
            $this->user_token = $_COOKIE[$this->token_cookie];
        }
    }

    /**
     * 进行基本的API操作请求。
     * @param array $post_data 用于POST的关联数组。
     * @return string  如果成功返回内容，如果失败返回false。
     */
    public function apiPost($post_data) {
        $post_data["SDK_VERSION"] = $this->api_config->SDK_VERSION;
        if($this->user_token != "") {
            $post_data["token"] = $this->user_token;
        }
        return $this->post($this->api_config->API_URL, $post_data);
    }

    /**
     * 获取网站接口的地址。
     * @return string
     */
    public function getPostURL() {
        return $this->api_config->API_URL;
    }

    /**
     * 获取用户的令牌，如果同时拥有正确的用户名和密码，则默认得到了用户的全部许可，通常用于网站外客户端的制作。
     * 如果没有用户名和密码，则只能是网站内部的应用，网站会根据已登录用户的记录来进行许可的授权。
     * @param string $name 用户名
     * @param string $password 密码
     * @return string  如果成功返回用户的令牌，如果失败返回false。
     */
    public function getUserToken($name, $password = "") {
        $post_data = array();
        $post_data["method"] = "token";
        $post_data["name"] = $name;
        $post_data["API_KEY"] = $this->api_config->API_KEY;
        if($password != "") {
            $post_data["password"] = $password;
        }
        $result = $this->apiPost($post_data);
        if($result) {
            $result = json_decode($result);
            $this->user_token = $result->token;
            setcookie($this->token_cookie, $this->user_token, time() + 86400, "/");
        } else {
            $this->user_token = "";
        }
        return $this->user_token;
    }

    /**
     * 直接获得当前存储的令牌，不进行远程查询。
     * @return string 用户令牌
     */
    public function getUserTokenWithoutRequest() {
        return $this->user_token;
    }

    public function setUserToken($token) {
        $this->user_token = $token;
    }

    /**
     * 释放令牌。
     */
    public function releaseUserToken() {
        $this->user_token = "";
        setcookie($this->token_cookie, "", time() - 1, "/");
    }

    /**
     * 获取用户的基础信息。
     * @return array 返回是一个关联数组，包括用户的id、用户名name、用户昵称nickname、用户的类型type。
     * 用户的类型为一个字符串，分为Normal：一般用户，Star：星级用户，VIP：重要用户，Admin：管理员。
     */
    public function getUserBasic() {
        $post_data = array();
        $post_data["method"] = "user.basic";
        $result = $this->apiPost($post_data);
        if($result) {
            $result = json_decode($result);
            return $result;
        }
        return array();
    }

    /**
     * 获取用户相册的数量。
     * @return int 相册数量
     */
    public function countAlbum() {
        $post_data = array();
        $post_data["method"] = "album.count";
        $result = $this->apiPost($post_data);
        if($result) {
            $result = json_decode($result);
            return $result->number;
        }
        return 0;
    }

    /**
     * 获取相册照片的数量。
     * @param int $albumID 相册ID
     * @return int 照片数量
     */
    public function countPhoto($albumID) {
        $post_data = array();
        $post_data["method"] = "photo.count";
        $post_data["album_id"] = $albumID;
        $result = $this->apiPost($post_data);
        if($result) {
            $result = json_decode($result);
            return $result->number;
        }
        return 0;
    }

    /**
     * 删除用户的相册，同时删除相册里面的所有图片。
     * @param int $albumID 相册的ID，在获取相册信息时可以得到。
     * @return bool 如果成功返回true，否则返回false。
     */
    public function deleteAlbum($albumID) {
        $post_data = array();
        $post_data["method"] = "album.delete";
        $post_data["album_id"] = $albumID;
        $result = $this->apiPost($post_data);
        if($result) {
            $result = json_decode($result);
            return $result->return == "true";
        }
        return false;
    }

    /**
     * 删除用户的照片。
     * @param int $photoID 照片的ID，在获取照片信息时可以得到。
     * @return bool 如果成功返回true，否则返回false。
     */
    public function deletePhoto($photoID) {
        $post_data = array();
        $post_data["method"] = "photo.delete";
        $post_data["photo_id"] = $photoID;
        $result = $this->apiPost($post_data);
        if($result) {
            $result = json_decode($result);
            return $result->return == "true";
        }
        return false;
    }

    /**
     * 新建相册。
     * @param string $name 相册的名称。
     * @param string $description 相册的描述。
     * @param string $type 相册的类型。
     * @return int 新建相册的ID。
     */
    public function insertAlbum($name, $description, $type) {
        $post_data = array();
        $post_data["method"] = "album.insert";
        $post_data["album_name"] = $name;
        $post_data["album_description"] = $description;
        $post_data["album_type"] = $type;
        $result = $this->apiPost($post_data);
        if($result) {
            $result = json_decode($result);
            if(isset($result->album_id)) {
                return $result->album_id;
            }
        }
        return "0";
    }

    /**
     * 上传照片。
     * @param string $albumID 相册的ID。
     * @param string $description 对于照片的描述。
     * @param string $photoPath 要上传的照片在本地的位置。
     * @return int 上传照片后的ID。
     */
    public function insertPhoto($albumID, $photoPath) {
        $post_data = array();
        $post_data["method"] = "photo.insert";
        $post_data["album_id"] = $albumID;
        $post_data["upload"] = "@" . $photoPath;
        $result = $this->apiPost($post_data);
        if($result) {
            $result = json_decode($result);
            if(isset($result->album_id)) {
                return $result->album_id;
            }
        }
        return 0;
    }

    /**
     * 获得全部相册的信息。
     * @param int $start 起始位置
     * @param int $number 选取的数量
     * @return array 返回是一个数组，数组中的每一项是一个stdClass，包含AlbumID相册ID、Album_Name相册名、Album_Description相册描述、Album_Type相册类型、Album_Indice相册用于排序的索引。
     */
    public function selectAlbums($start = 0, $number = 0) {
        $post_data = array();
        $post_data["method"] = "album.select";
        if($start || $number) {
            $post_data["limit_start"] = $start;
            $post_data["limit_number"] = $number;
        }
        $result = $this->apiPost($post_data);
        if($result) {
            $result = json_decode($result);
            return $result;
        }
        return array();
    }

    /**
     * 获得指定相册的信息。
     * @param int $albumID 相册的ID。
     * @return stdClass @see selectAllAlbums()
     */
    public function selectAlbumById($albumID) {
        $post_data = array();
        $post_data["method"] = "album.select";
        $post_data["album_id"] = $albumID;
        $result = $this->apiPost($post_data);
        if($result) {
            $result = json_decode($result);
            if(count($result) > 0) {
                return $result[0];
            }
        }
        return array();
    }

    /**
     * 获得相册中的全部照片信息。
     * @param int $albumID 相册的ID。
     * @param int $start 起始位置
     * @param int $number 选取的数量
     * @return array 返回的是一个数组，数组中的每一项是一个stdClass，包含PhotoID照片ID、AlbumID所属相册的ID、Description照片描述、Indice用于照片排序的索引。
     */
    public function selectPhotos($albumID, $start, $number) {
        $post_data = array();
        $post_data["method"] = "photo.select";
        $post_data["album_id"] = $albumID;
        if($start || $number) {
            $post_data["limit_start"] = $start;
            $post_data["limit_number"] = $number;
        }
        $result = $this->apiPost($post_data);
        if($result) {
            $result = json_decode($result);
            return $result;
        }
        return array();
    }

    /**
     * 获取指定照片的信息。
     * @param int $photoID 照片的ID。
     * @return stdClass @see selectAllPhotos()
     */
    public function selectPhotoById($photoID) {
        $post_data = array();
        $post_data["method"] = "photo.select";
        $post_data["photo_id"] = $photoID;
        $result = $this->apiPost($post_data);
        if($result) {
            $result = json_decode($result);
            if(count($result) > 0) {
                return $result[0];
            }
        }
        return array();
    }

    /**
     * 更新相册信息。
     * @param int $albumID 相册的ID。
     * @param string $name 相册的名称。
     * @param string $description 相册的描述。
     * @param int $type 相册的类型。
     * @param int $indice 相册的排序索引。
     * @return bool 如果成功返回true，否则返回false。
     */
    public function updateAlbum($albumID, $name, $description, $type, $indice) {
        $post_data = array();
        $post_data["method"] = "album.update";
        $post_data["album_id"] = $albumID;
        $post_data["album_name"] = $name;
        $post_data["album_description"] = $description;
        $post_data["album_type"] = $type;
        $post_data["album_indice"] = $indice;
        $result = $this->apiPost($post_data);
        if($result) {
            print_r($result);
            $result = json_decode($result);
            return $result->return == "true";
        }
        return false;
    }

    /**
     * 更新照片信息。
     * @param int $photoID 照片的ID。
     * @param int $albumID 所属相册的ID。
     * @param string $description 照片的描述。
     * @param int $indice 照片的排序索引。
     * @return bool 如果成功返回true，否则返回false。
     */
    public function updatePhoto($photoID, $albumID, $description, $indice) {
        $post_data = array();
        $post_data["method"] = "photo.update";
        $post_data["photo_id"] = $photoID;
        $post_data["album_id"] = $albumID;
        $post_data["photo_description"] = $description;
        $post_data["photo_indice"] = $indice;
        $result = $this->apiPost($post_data);
        if($result) {
            $result = json_decode($result);
            return $result->return == "true";
        }
        return false;
    }
}

?>
