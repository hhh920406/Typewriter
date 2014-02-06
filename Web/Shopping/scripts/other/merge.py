# -*- coding: utf-8 -*- 

import os
import shutil

root_path = "items"
for seller_dir in os.listdir("fiftynine"):
    seller_dir = os.path.join("fiftynine", seller_dir)
    for category_dir in os.listdir(seller_dir):
        type = category_dir.split(',')[0]
        category_path = os.path.join(root_path, type)
        if not os.path.exists(category_path):
            os.makedirs(category_path)        
        category_dir = os.path.join(seller_dir, category_dir)
        for file in os.listdir(category_dir):
            target_path = os.path.join(category_path, file) 
            if not os.path.isfile(target_path):
                file = os.path.join(category_dir, file)
                shutil.copy(file, category_path)
                print "Copy: " + file + " " + target_path;
