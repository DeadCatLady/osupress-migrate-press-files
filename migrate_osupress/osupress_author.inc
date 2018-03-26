<?php

/**
 * @file
 * Press author Migrations
 */

/**
 * Pressauthor Migration node.
 */

class MigratePressAuthorMigration extends DrupalNode6Migration {
    public function __construct($arguments) {
      parent::__construct($arguments);

      $this->addFieldMapping('field_press_author_last_name', 'field_lastname');

      $this->addFieldMapping('field_press_author_webpage', 'field_website');
      $this->addFieldMapping('field_press_author_link', 'field_website');  
      // Not sure how to make the source text into a link -_-
      // $this->addFieldMapping('field_press_author_link:attributes')
      //       ->defaultValue('');      

      $this->addFieldMapping('field_press_author_picture', 'field_photo', TRUE)
            ->sourceMigration('OSUPressFile');
      $this->addFieldMapping('field_press_author_picture:file_class')
            ->defaultValue('MigrateFileFid');
      $this->addFieldMapping('field_press_author_picture:preserve_files')
            ->defaultValue(TRUE);
      $this->addFieldMapping('field_press_author_picture:alt')
            ->defaultValue(t('Picture of the author'));

      $this->addFieldMapping('field_press_author_biography', 'field_bio');     

      

    }  

    public function getConnection($connection = 'osupress'){
      return Database::getConnection('default', $connection);
    }


}
