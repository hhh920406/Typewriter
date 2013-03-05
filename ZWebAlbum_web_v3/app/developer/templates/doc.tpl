<div class = "docDiv">
    <h1>一、基本说明</h1>
    　　网站提供通信的接口，可以使用POST的方式传递参数。每次必须传递API Key的数值，API Key是申请开发应用后得到的密钥，一般情况下不得向其他无关人员透漏。如果是站内应用，是使用用户名作为query string传递，这时能够进行的功能是受限的，必需得到用户足够的许可才能进行制定的操作。如果是站外应用则需要使用用户名和密码登录，这时默认拥有用户的全部许可，可以执行提供的接口中的全部的操作。
    <h1>二、参数说明</h1>
    　　每次POST，method是必须填写的操作，根据method的不同会执行不同的操作，接下来说明在method取值不同的情况下参数的填写和获得的结果。如果使用官方提供的SDK，用户可以不考虑method的取值，返回结果全部是json格式。
    <h2>token</h2>
    站内应用只传递[name]用户名即可，桌面应用传递[name]用户名和[password]密码。
    <h2>user.basic</h2>
    无需传递多余参数。
    <h2>album.delete</h2>
    传递参数[album_id]，删除对应相册ID的相册。
    <h2>album.insert</h2>
    传递参数[album_name]相册名，[album_description]相册描述，[album_type]相册类型即可创建相册。<br/>
    返回值是新建相册的ID。
    <h2>album.select</h2>
    如果不传递多余参数，则返回当前用户的全部相册。<br/>
    如果传递参数[album_id]，则返回对应相册ID的信息。<br/>
    如果传递参数[album_name]，则返回对应相册名称的信息。
    <h2>album.update</h2>
    传递参数[album_id]相册ID，[album_name]相册名，[album_description]相册描述，[album_type]相册类型即可修改相册信息。
    <h2>photo.delete</h2>
    传递参数[photo_id]，删除对应照片ID的照片。
    <h2>photo.insert</h2>
    传递参数[album_id]相册ID，[photo_description]照片描述，[photo_path]照片在本地所在地址即可上传照片。<br/>
    返回值是最新照片的ID。
    <h2>photo.select</h2>
    如果传递参数[album_id]，则返回对应相册ID的信息。<br/>
    如果传递参数[photo_id]，则返回对应照片ID的信息。
    <h2>photo.update</h2>
    传递参数[photo_id]照片ID，[album_id]相册ID，[photo_description]照片描述，[photo_path]照片即可修改照片信息。
</div>