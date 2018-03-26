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

      /**
       * Author's last name
       */
      $this->addFieldMapping('field_press_author_last_name', 'field_lastname');

      /**
       * Author's webpage.
       * The field_press_author_link is a link, and the field_website
       * is a text field. The migration will still work correctly with the 
       * field types being different.
       */
      $this->addFieldMapping('field_press_author_link', 'field_website');     

      /**
       * Author's picture
       */
      $this->addFieldMapping('field_press_author_picture', 'field_photo', TRUE)
            ->sourceMigration('OSUPressFile');
      $this->addFieldMapping('field_press_author_picture:file_class')
            ->defaultValue('MigrateFileFid');
      $this->addFieldMapping('field_press_author_picture:preserve_files')
            ->defaultValue(TRUE);
      $this->addFieldMapping('field_press_author_picture:alt')
            ->defaultValue(t('Picture of the author'));

      /**
       * Author's biography
       */
      $this->addFieldMapping('field_press_author_biography', 'field_bio'); 
      $this->addFieldMapping('field_press_author_biography:format')
            ->defaultValue('filtered_html');     

      

    }  

    public function getConnection($connection = 'osupress'){
      return Database::getConnection('default', $connection);
    }


}
