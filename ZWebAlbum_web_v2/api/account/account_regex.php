<?php

/**
 * Matching strings in account control.
 * @author ZHG 
 */
class Account_Regex
{

    /**
     * Judge if the string contains only upper and lower English characters, numbers and underscore, and the length is between 6 and 20 inclusive.
     * @param string $subject The string to be judged.
     * @param integer Return 1 if the string meet the conditions, else return 0. 
     */
    public static function isTextSimple($subject)
    {
        $pattern = "/^[A-za-z0-9_]{6,20}$/";
        if(preg_match($pattern, $subject))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    /**
     * Judge if the string represents a E-mail address.
     * @param string $subject The string to be judged.
     * @param integer Return 1 if the string meet the conditions, else return 0. 
     */
    public static function isEmail($subject)
    {
        $pattern = "/^([a-z0-9_.-]+)@([da-z.-]+).([a-z.]{2,6})$/";
        if(preg_match($pattern, $subject))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}
?>
