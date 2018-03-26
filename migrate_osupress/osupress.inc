<?php

/**
 * @file
 * Pressbook Migrations
 */

/**
 * Pressbook Migration node.
 */

class MigratePressBookMIgration extends DrupalNode6Migration {
    public function __construct($arguments) {
      parent::__construct($arguments);

      /**
       * Book cover
       */
        $this->addFieldMapping('field_press_book_cover', 'field_cover', TRUE)
              ->sourceMigration('OSUPressFile');
        $this->addFieldMapping('field_press_book_cover:file_class')
              ->defaultValue('MigrateFileFid');
        $this->addFieldMapping('field_press_book_cover:preserve_files')
              ->defaultValue(TRUE);
        $this->addFieldMapping('field_press_book_cover:title')
              ->defaultValue(t('Book cover'));

      $this->addFieldMapping('field_press_book_subtitle', 'field_subtitle', TRUE);

      /**
       * Book author
       */
      $this->addFieldMapping('field_press_book_authors_editior', 'field_author', TRUE);
           // ->sourceMigration('OSUPressNodeauthor');
      $this->addFieldMapping('field_test_uthors_editors_test', 'field_author', TRUE);


      /**
       * Main book info
       */
      $this->addFieldMapping('field_press_book_subtitle:format', NULL, TRUE)->defaultValue('plain_text');
      $this->addFieldMapping('field_press_book_edition', 'field_edition', TRUE);
      $this->addFieldMapping('field_press_book_copublisher', 'field_copublisher', TRUE);
      $this->addFieldMapping('field_press_book_add_contribs', 'field_contributors', TRUE);
      $this->addFieldMapping('field_press_book_series_name', 'field_series', TRUE);
      
      /**
       * Book taxonomy
       */
      $this->addFieldMapping('field_press_taxonomy', '1')
            ->sourceMigration('OSUPressTerm1');
      $this->addFieldMapping('field_press_taxonomy:source_type')
            ->defaultValue('tid');


      /**
       * Paperback group
       */
      $this->addFieldMapping('field_press_book_paper_isbn', 'field_paper_isbn', TRUE);
      $this->addFieldMapping('field_press_book_paper_pub_month', 'field_paper_month', TRUE);
      $this->addFieldMapping('field_press_book_paper_pub_year', 'field_paper_year', TRUE);
      $this->addFieldMapping('field_press_book_paper_pub_seaso', 'field_paper_season', TRUE);
      $this->addFieldMapping('field_press_book_paper_price', 'field_paper_price', TRUE);
      $this->addFieldMapping('field_press_book_paper_discount', 'field_paper_discount', TRUE);

      /**
       * Hardcover group
       */
      $this->addFieldMapping('field_press_book_hardcover_isbn', 'field_hardcover_isbn', TRUE);
      $this->addFieldMapping('field_press_book_hc_pub_mon', 'field_hardcover_month', TRUE);
      $this->addFieldMapping('field_press_book_hc_pub_year', 'field_hardcover_year', TRUE);
      $this->addFieldMapping('field_press_book_hc_pub_season', 'field_hardcover_season', TRUE);
      $this->addFieldMapping('field_press_book_hc_price', 'field_hardcover_price', TRUE);
      $this->addFieldMapping('field_press_hc_short_discount', 'field_hardcover_discount', TRUE);

      /**
       * E book group
       */
      $this->addFieldMapping('field_press_e_book_isbn	', 'field_ebook_isbn', TRUE);
      $this->addFieldMapping('field_press_e_book_pub_month', 'field_ebook_month', TRUE);
      $this->addFieldMapping('field_press_e_book_pub_year', 'field_ebook_year', TRUE);
      $this->addFieldMapping('field_press_e_book_pub_season', 'field_ebook_season', TRUE);
      $this->addFieldMapping('field_press_e_book_price', 'field_ebook_price', TRUE);
      $this->addFieldMapping('field_press_e_book_short_disc', 'field_ebook_discount', TRUE);
      
      /**
       * Status group
       */
      $this->addFieldMapping('field_press_field_status', 'field_status', TRUE);
      $this->addFieldMapping('field_press_status_description', 'field_status_desc', TRUE);

      /**
       * Main content of the book, intro, ect.
       */
      $this->addFieldMapping('field_press_trim_size', 'field_trim', TRUE);
      $this->addFieldMapping('field_press_pages', 'field_pages', TRUE);
      $this->addFieldMapping('field_press_inclusion_data_list', 'field_inclusion', TRUE);
      $this->addFieldMapping('field_press_table_of_contents', 'field_toc', TRUE);
      $this->addFieldMapping('field_press_table_of_contents:format')->defaultValue('filtered_html');
      $this->addFieldMapping('field_press_introduction', 'field_intro', TRUE);
      $this->addFieldMapping('field_press_introduction:format')->defaultValue('filtered_html');
      $this->addFieldMapping('field_press_excerpt', 'field_sample', TRUE);
      $this->addFieldMapping('field_press_excerpt:format')->defaultValue('filtered_html');
      $this->addFieldMapping('field_press_book_description', 'field_desc', TRUE);
      $this->addFieldMapping('field_press_book_description:format')->defaultValue('filtered_html');
      $this->addFieldMapping('field_press_reviews', 'field_reviews', TRUE);
      $this->addFieldMapping('field_press_reviews:format')->defaultValue('filtered_html');
    }  

    public function getConnection($connection = 'osupress'){
      return Database::getConnection('default', $connection);
    }

    public function prepareRow($row) {
          if (parent::prepareRow($row) == NULL) {
                return parent::prepareRow($row);
          }
          // DB query to get the NID of the author and return it back to the field
          // Making destination db active.
          db_set_active('default');
          // Getting the NID of the author node.
          $this->queueMessage('We are trying to migrate '. $row->field_test_uthors_editors_test);
          $author_nid = db_select('node', 'n')
            ->fields('n', array('nid'))
            ->condition('type', 'press_author')
            ->condition('title', $row->field_author)
            ->execute()
            ->fetchAssoc();
          // Seting the data back for the import.
          $this->queueMessage('Got this NID back '. $author_nid);
          $row->field_author = $author_nid['nid'];

    }


}
