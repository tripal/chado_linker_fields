<?php

/**
 * Implements hook_bundle_fields_info().
 *
 * This is a Tripal defined hook that supports integration with the
 * TripalEntity field.
 */
function chado_linker_fields_bundle_fields_info($entity_type, $bundle) {

  $chado_bundle = db_select('chado_bundle', 'cb')
    ->fields('cb')
    ->condition('bundle_id', $bundle->id)
    ->execute()
    ->fetchObject();

  // Get the details about the mapping of this bundle to the Chado table:
  $details = [
    'chado_cvterm_id' => $chado_bundle->type_id,
    'chado_table' => $chado_bundle->data_table,
    'chado_type_table' => $chado_bundle->type_linker_table,
    'chado_type_id' => $chado_bundle->type_id,
    'chado_type_column' => $chado_bundle->type_column,
    'chado_type_value' => $chado_bundle->type_value,
    'chado_base_type_id' => $chado_bundle->base_type_id,
  ];

  $info = [];

  // Create fields for linking tables.
  chado_linker_fields_bundle_fields_info_linker($info, $details, $entity_type, $bundle);

  return $info;

}

/**
 *
 * @param $details
 */
function chado_linker_fields_bundle_fields_info_linker(&$info, $details, $entity_type, $bundle) {

  $table_name = $details['chado_table'];
  $type_table = $details['chado_type_table'];
  $type_column = $details['chado_type_column'];
  $cvterm_id = $details['chado_cvterm_id'];
  $type_value = $details['chado_type_value'];

  // ANALYSES
  $analysis_table = $table_name . '_analysis';
  if (!chado_table_exists($analysis_table)) {
    $analysis_table = 'analysis_' . $table_name;
  }
  // Also supports analysisfeature table.
  if (!chado_table_exists($analysis_table)) {
    $analysis_table = 'analysis' . $table_name;
  }
  if (chado_table_exists($analysis_table)) {
    $schema = chado_get_schema($analysis_table);
    $pkey = $schema['primary key'][0];
    $field_name = $table_name . '_analysis';
    $field_type = 'chado_linker__analysis';
    $info[$field_name] = [
      'field_name' => $field_name,
      'type' => $field_type,
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,
      'locked' => FALSE,
      'storage' => [
        'type' => 'field_chado_storage',
      ],
    ];
  }

  // ASSAYS
  $assay_table = $table_name . '_assay';
  if (!chado_table_exists($assay_table)) {
    $assay_table = 'assay_' . $table_name;
  }
  if (chado_table_exists($assay_table)) {
    $schema = chado_get_schema($assay_table);
    $pkey = $schema['primary key'][0];
    $field_name = $table_name . '_assay';
    $field_type = 'chado_linker__assay';
    $info[$field_name] = [
      'field_name' => $field_name,
      'type' => $field_type,
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,
      'locked' => FALSE,
      'storage' => [
        'type' => 'field_chado_storage',
      ],
    ];
  }

  // BIOMATERIALS
  // supports biomaterial as either prefix or suffix of linker table name
  $biomaterial_table = $table_name . '_biomaterial';
  if (!chado_table_exists($biomaterial_table)) {
    $biomaterial_table = 'biomaterial_' . $table_name;
  }
  if (chado_table_exists($biomaterial_table)) {
    $schema = chado_get_schema($biomaterial_table);
    $pkey = $schema['primary key'][0];
    $field_name = $table_name . '_biomaterial';
    $field_type = 'chado_linker__biomaterial';
    $info[$field_name] = [
      'field_name' => $field_name,
      'type' => $field_type,
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,
      'locked' => FALSE,
      'storage' => [
        'type' => 'field_chado_storage',
      ],
    ];
  }

  // FEATURES
  $feature_table = $table_name . '_feature';
  if (!chado_table_exists($feature_table)) {
    $feature_table = 'feature_' . $table_name;
  }
  // Also supports analysisfeature table.
  if (!chado_table_exists($feature_table)) {
    $feature_table = $table_name . 'feature';
  }
  if (chado_table_exists($feature_table)) {
    $schema = chado_get_schema($feature_table);
    $pkey = $schema['primary key'][0];
    $field_name = $table_name . '_feature';
    $field_type = 'chado_linker__feature';
    $info[$field_name] = [
      'field_name' => $field_name,
      'type' => $field_type,
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,
      'locked' => FALSE,
      'storage' => [
        'type' => 'field_chado_storage',
      ],
    ];
  }

  // FEATUREMAPS
  $featuremap_table = $table_name . '_featuremap';
  if (!chado_table_exists($featuremap_table)) {
    $featuremap_table = 'featuremap_' . $table_name;
  }
  if (chado_table_exists($featuremap_table)) {
    $schema = chado_get_schema($featuremap_table);
    $pkey = $schema['primary key'][0];
    $field_name = $table_name . '_featuremap';
    $field_type = 'chado_linker__featuremap';
    $info[$field_name] = [
      'field_name' => $field_name,
      'type' => $field_type,
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,
      'locked' => FALSE,
      'storage' => [
        'type' => 'field_chado_storage',
      ],
    ];
  }

  // ORGANISMS
  $organism_table = 'organism_' . $table_name;
  if (!chado_table_exists($organism_table)) {
    $organism_table = $table_name . '_organism';
  }
  if (chado_table_exists($organism_table)) {
    $schema = chado_get_schema($organism_table);
    $pkey = $schema['primary key'][0];
    $field_name = $table_name . '_organism';
    $field_type = 'chado_linker__organism';
    $info[$field_name] = [
      'field_name' => $field_name,
      'type' => $field_type,
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,
      'locked' => FALSE,
      'storage' => [
        'type' => 'field_chado_storage',
      ],
    ];
  }

  // PROJECTS
  // supports project as either prefix or suffix of linker table name
  $project_table = 'project_' . $table_name;
  if (!chado_table_exists($project_table)) {
    $project_table = $table_name . '_project';
  }
  if (chado_table_exists($project_table)) {
    $schema = chado_get_schema($project_table);
    $pkey = $schema['primary key'][0];
    $field_name = $table_name . '_project';
    $field_type = 'chado_linker__project';
    $info[$field_name] = [
      'field_name' => $field_name,
      'type' => $field_type,
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,
      'locked' => FALSE,
      'storage' => [
        'type' => 'field_chado_storage',
      ],
    ];
  }

  // STOCKS
  // supports stock as either prefix or suffix of linker table name
  $stock_table = $table_name . '_stock';
  // Unfortunately a special case here, mainlab tripal defines a chado.feature_stock
  // table conflicting with the tripal chado.stock_feature table, similarly with
  // chado.featuremap_stock, chado.library_stock
  if (($table_name == 'feature') or ($table_name == 'featuremap')
    or ($table_name == 'library') or (!chado_table_exists($stock_table))) {
    $stock_table = 'stock_' . $table_name;
  }
  if (chado_table_exists($stock_table)) {
    $schema = chado_get_schema($stock_table);
    $pkey = $schema['primary key'][0];
    $field_name = $table_name . '_stock';
    $field_type = 'chado_linker__stock';
    $info[$field_name] = [
      'field_name' => $field_name,
      'type' => $field_type,
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,
      'locked' => FALSE,
      'storage' => [
        'type' => 'field_chado_storage',
      ],
    ];
  }

  // STUDIES
  // supports study as either prefix or suffix of linker table name
  $study_table = 'study_' . $table_name;
  if (!chado_table_exists($study_table)) {
    $study_table = $table_name . '_study';
  }
  if (chado_table_exists($study_table)) {
    $schema = chado_get_schema($study_table);
    $pkey = $schema['primary key'][0];
    $field_name = $table_name . '_study';
    $field_type = 'chado_linker__study';
    $info[$field_name] = [
      'field_name' => $field_name,
      'type' => $field_type,
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,
      'locked' => FALSE,
      'storage' => [
        'type' => 'field_chado_storage',
      ],
    ];
  }

}

/**
 * Implements hook_create_tripalfield_instance().
 *
 * This is a Tripal defined hook that supports integration with the
 * TripalEntity field.
 */
function chado_linker_fields_bundle_instances_info($entity_type, $bundle) {

  $chado_bundle = db_select('chado_bundle', 'cb')
    ->fields('cb')
    ->condition('bundle_id', $bundle->id)
    ->execute()
    ->fetchObject();

  $details = [
    'chado_cvterm_id' => $chado_bundle->type_id,
    'chado_table' => $chado_bundle->data_table,
    'chado_type_table' => $chado_bundle->type_linker_table,
    'chado_type_id' => $chado_bundle->type_id,
    'chado_type_column' => $chado_bundle->type_column,
    'chado_type_value' => $chado_bundle->type_value,
    'chado_base_type_id' => $chado_bundle->base_type_id,
  ];

  $info = [];
  chado_linker_fields_bundle_instances_info_linker($info, $entity_type, $bundle, $details);

  return $info;

}

/**
 *
 * @param unknown $entity_type
 * @param unknown $bundle
 * @param unknown $details
 */
function chado_linker_fields_bundle_instances_info_linker(&$info, $entity_type, $bundle, $details) {

  $table_name = $details['chado_table'];
  $type_table = $details['chado_type_table'];
  $type_column = $details['chado_type_column'];
  $cvterm_id = $details['chado_cvterm_id'];
  $type_value = $details['chado_type_value'];

  // ANALYSES
  $analysis_table = $table_name . '_analysis';
  if (!chado_table_exists($analysis_table)) {
    $analysis_table = 'analysis_' . $table_name;
  }
  // Also supports analysisfeature table.
  if (!chado_table_exists($analysis_table)) {
    $analysis_table = 'analysis' . $table_name;
  }
  if (chado_table_exists($analysis_table)) {
    $field_name = $table_name . '_analysis';
    $info[$field_name] = $info[$field_name] = [
      'field_name' => $field_name,
      'entity_type' => $entity_type,
      'bundle' => $bundle->name,
      'label' => 'Analysis',
      'description' => 'Associates an analysis with this record',
      'required' => FALSE,
      'settings' => [
        'auto_attach' => FALSE,
        'chado_table' => $analysis_table,
        'base_table' => $table_name,
        'chado_column' => 'analysis_id',
        'term_accession' => 'C25391',
        'term_vocabulary' => 'NCIT',
        'term_name' => 'Analysis',
      ],
      'widget' => [
        'type' => 'chado_linker__analysis_widget',
        'settings' => [
          'display_label' => 1,
        ],
      ],
      'display' => [
        'default' => [
          'label' => 'inline',
          'type' => 'chado_linker__analysis_formatter',
          'settings' => [],
        ],
      ],
    ];
  }

  // ASSAYS
  $assay_table = $table_name . '_assay';
  if (!chado_table_exists($assay_table)) {
    $assay_table = 'assay_' . $table_name;
  }
  if (chado_table_exists($assay_table)) {
    $field_name = $table_name . '_assay';
    $info[$field_name] = $info[$field_name] = [
      'field_name' => $field_name,
      'entity_type' => $entity_type,
      'bundle' => $bundle->name,
      'label' => 'Assay',
      'description' => 'Associates an assay with this record',
      'required' => FALSE,
      'settings' => [
        'auto_attach' => FALSE,
        'chado_table' => $assay_table,
        'base_table' => $table_name,
        'chado_column' => 'assay_id',
        'term_accession' => 'C60819',
        'term_vocabulary' => 'NCIT',
        'term_name' => 'Assay',
      ],
      'widget' => [
        'type' => 'chado_linker__assay_widget',
        'settings' => [
          'display_label' => 1,
        ],
      ],
      'display' => [
        'default' => [
          'label' => 'inline',
          'type' => 'chado_linker__assay_formatter',
          'settings' => [],
        ],
      ],
    ];
  }

  // BIOMATERIALS
  // supports biomaterial as either prefix or suffix of linker table name
  $biomaterial_table = $table_name . '_biomaterial';
  if (!chado_table_exists($biomaterial_table)) {
    $biomaterial_table = 'biomaterial_' . $table_name;
  }
  if (chado_table_exists($biomaterial_table)) {
    $field_name = $table_name . '_biomaterial';
    $info[$field_name] = $info[$field_name] = [
      'field_name' => $field_name,
      'entity_type' => $entity_type,
      'bundle' => $bundle->name,
      'label' => 'Biomaterial',
      'description' => 'Associates a biomaterial with this record',
      'required' => FALSE,
      'settings' => [
        'auto_attach' => FALSE,
        'chado_table' => $biomaterial_table,
        'base_table' => $table_name,
        'chado_column' => 'biomaterial_id',
        'term_accession' => 'C43376',
        'term_vocabulary' => 'NCIT',
        'term_name' => 'Biologically-Derived Material ',
      ],
      'widget' => [
        'type' => 'chado_linker__biomaterial_widget',
        'settings' => [
          'display_label' => 1,
        ],
      ],
      'display' => [
        'default' => [
          'label' => 'inline',
          'type' => 'chado_linker__biomaterial_formatter',
          'settings' => [],
        ],
      ],
    ];
  }

  // FEATURES
  $feature_table = $table_name . '_feature';
  if (!chado_table_exists($feature_table)) {
    $feature_table = 'feature_' . $table_name;
  }
  // Also supports analysisfeature table.
  if (!chado_table_exists($feature_table)) {
    $feature_table = $table_name . 'feature';
  }
  if (chado_table_exists($feature_table)) {
    $field_name = $table_name . '_feature';
    $info[$field_name] = $info[$field_name] = [
      'field_name' => $field_name,
      'entity_type' => $entity_type,
      'bundle' => $bundle->name,
      'label' => 'Feature',
      'description' => 'Associates a feature with this record',
      'required' => FALSE,
      'settings' => [
        'auto_attach' => FALSE,
        'chado_table' => $feature_table,
        'base_table' => $table_name,
        'chado_column' => 'feature_id',
        'term_accession' => 'C73619',
        'term_vocabulary' => 'NCIT',
        'term_name' => 'Feature',
      ],
      'widget' => [
        'type' => 'chado_linker__feature_widget',
        'settings' => [
          'display_label' => 1,
        ],
      ],
      'display' => [
        'default' => [
          'label' => 'inline',
          'type' => 'chado_linker__feature_formatter',
          'settings' => [],
        ],
      ],
    ];
  }

  // FEATUREMAPS
  $featuremap_table = $table_name . '_featuremap';
  if (!chado_table_exists($featuremap_table)) {
    $featuremap_table = 'featuremap_' . $table_name;
  }
  if (chado_table_exists($featuremap_table)) {
    $field_name = $table_name . '_featuremap';
    $info[$field_name] = $info[$field_name] = [
      'field_name' => $field_name,
      'entity_type' => $entity_type,
      'bundle' => $bundle->name,
      'label' => 'Featuremap',
      'description' => 'Associates a featuremap with this record',
      'required' => FALSE,
      'settings' => [
        'auto_attach' => FALSE,
        'chado_table' => $featuremap_table,
        'base_table' => $table_name,
        'chado_column' => 'featuremap_id',
        'term_accession' => '1274',
        'term_vocabulary' => 'data',
        'term_name' => 'Map',
      ],
      'widget' => [
        'type' => 'chado_linker__featuremap_widget',
        'settings' => [
          'display_label' => 1,
        ],
      ],
      'display' => [
        'default' => [
          'label' => 'inline',
          'type' => 'chado_linker__featuremap_formatter',
          'settings' => [],
        ],
      ],
    ];
  }

  // ORGANISMS
  $organism_table = 'organism_' . $table_name;
  if (!chado_table_exists($organism_table)) {
    $organism_table = $table_name . '_organism';
  }
  if (chado_table_exists($organism_table)) {
    $field_name = $table_name . '_organism';
    $info[$field_name] = $info[$field_name] = [
      'field_name' => $field_name,
      'entity_type' => $entity_type,
      'bundle' => $bundle->name,
      'label' => 'Organism',
      'description' => 'Associates an organism with this record',
      'required' => FALSE,
      'settings' => [
        'auto_attach' => FALSE,
        'chado_table' => $organism_table,
        'base_table' => $table_name,
        'chado_column' => 'organism_id',
        'term_accession' => 'C14250',
        'term_vocabulary' => 'NCIT',
        'term_name' => 'organism',
      ],
      'widget' => [
        'type' => 'chado_linker__organism_widget',
        'settings' => [
          'display_label' => 1,
        ],
      ],
      'display' => [
        'default' => [
          'label' => 'inline',
          'type' => 'chado_linker__organism_formatter',
          'settings' => [],
        ],
      ],
    ];
  }

  // PROJECTS
  // supports project as either prefix or suffix of linker table name
  $project_table = 'project_' . $table_name;
  if (!chado_table_exists($project_table)) {
    $project_table = $table_name . '_project';
  }
  if (chado_table_exists($project_table)) {
    $field_name = $table_name . '_project';
    $info[$field_name] = $info[$field_name] = [
      'field_name' => $field_name,
      'entity_type' => $entity_type,
      'bundle' => $bundle->name,
      'label' => 'Project',
      'description' => 'Associates a project with this record',
      'required' => FALSE,
      'settings' => [
        'auto_attach' => FALSE,
        'chado_table' => $project_table,
        'base_table' => $table_name,
        'chado_column' => 'project_id',
        'term_accession' => 'C47885',
        'term_vocabulary' => 'NCIT',
        'term_name' => 'Project',
      ],
      'widget' => [
        'type' => 'chado_linker__project_widget',
        'settings' => [
          'display_label' => 1,
        ],
      ],
      'display' => [
        'default' => [
          'label' => 'inline',
          'type' => 'chado_linker__project_formatter',
          'settings' => [],
        ],
      ],
    ];
  }

  // STOCKS
  // supports stock as either prefix or suffix of linker table name
  $stock_table = $table_name . '_stock';
  // Unfortunately a special case here, mainlab tripal defines a chado.feature_stock
  // table conflicting with the tripal chado.stock_feature table, similarly with
  // chado.featuremap_stock, chado.library_stock
  if (($table_name == 'feature') or ($table_name == 'featuremap')
    or ($table_name == 'library') or (!chado_table_exists($stock_table))) {
    $stock_table = 'stock_' . $table_name;
  }
  if (chado_table_exists($stock_table)) {
    $field_name = $table_name . '_stock';
    $info[$field_name] = $info[$field_name] = [
      'field_name' => $field_name,
      'entity_type' => $entity_type,
      'bundle' => $bundle->name,
      'label' => 'Stock',
      'description' => 'Associates a stock with this record',
      'required' => FALSE,
      'settings' => [
        'auto_attach' => FALSE,
        'chado_table' => $stock_table,
        'base_table' => $table_name,
        'chado_column' => 'stock_id',
        'term_accession' => 'C48288',
        'term_vocabulary' => 'NCIT',
        'term_name' => 'Stock',
      ],
      'widget' => [
        'type' => 'chado_linker__stock_widget',
        'settings' => [
          'display_label' => 1,
        ],
      ],
      'display' => [
        'default' => [
          'label' => 'inline',
          'type' => 'chado_linker__stock_formatter',
          'settings' => [],
        ],
      ],
    ];
  }

  // STUDIES
  // supports study as either prefix or suffix of linker table name
  $study_table = 'study_' . $table_name;
  if (!chado_table_exists($study_table)) {
    $study_table = $table_name . '_study';
  }
  if (chado_table_exists($study_table)) {
    $field_name = $table_name . '_study';
    $info[$field_name] = $info[$field_name] = [
      'field_name' => $field_name,
      'entity_type' => $entity_type,
      'bundle' => $bundle->name,
      'label' => 'Study',
      'description' => 'Associates a study with this record',
      'required' => FALSE,
      'settings' => [
        'auto_attach' => FALSE,
        'chado_table' => $study_table,
        'base_table' => $table_name,
        'chado_column' => 'study_id',
        'term_accession' => 'C63536',
        'term_vocabulary' => 'NCIT',
        'term_name' => 'Study',
      ],
      'widget' => [
        'type' => 'chado_linker__study_widget',
        'settings' => [
          'display_label' => 1,
        ],
      ],
      'display' => [
        'default' => [
          'label' => 'inline',
          'type' => 'chado_linker__study_formatter',
          'settings' => [],
        ],
      ],
    ];
  }

}
