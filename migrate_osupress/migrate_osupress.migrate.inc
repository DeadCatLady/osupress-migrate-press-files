<?php

/**
 * Impelements hook_migrate_api().
 */
function migrate_osupress_migrate_api() {
  
  // Define our migrate array to start. We will add to it later.
  $api = array(
    'api' => 2,
    'groups'=> array(
      'press'=>array(
        'title'=>t('OSUPress Migration'),
      ),
    ),
    'migrations'=> array(),
  );
  
  // Common argumenst used for all migrations.
  $common_arguments = array(
    'source_version' => 6,
    'group_name' => 'press',
    'source_connection' => 'legacy',
  );
  
  // Pressbook content specific migrations.
  $pressbook_arguments = $common_arguments + array(
    'description' => t('Pressbook Migrations'),
    'class_name' => 'MigratePressBookMIgration',
    'group_name' => 'press',
    'source_type' => 'book',
    'destination_type' => 'press_book', 
    'machine_name' => 'Press Book',
  );

  //
  $pressauthor_arguments = $common_arguments + array(
    'description' => t('Pressbook Migrations'),
    'class_name' => 'MigratePressAuthorMigration',
    'group_name' => 'press',
    'source_type' => 'author',
    'destination_type' => 'press_author', 
    'machine_name' => 'Press Author',
  );

  // Add migration to the migrate array.
  $api['migrations']['pressbook'] = $pressbook_arguments;
  $api['migrations']['pressauthor'] = $pressauthor_arguments;

  // Return all migration information.
  return $api;
}