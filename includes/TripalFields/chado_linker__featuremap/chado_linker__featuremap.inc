<?php

class chado_linker__featuremap extends ChadoField {


  // --------------------------------------------------------------------------
  //                     EDITABLE STATIC CONSTANTS
  //
  // The following constants SHOULD be set for each descendent class.  They are
  // used by the static functions to provide information to Drupal about
  // the field and its default widget and formatter.
  // --------------------------------------------------------------------------

  // The default label for this field.
  public static $default_label = 'Featuremaps';

  // The default uniquename for this field.
  public static $uniquename = 'Associates a featuremap with this record';

  // Provide a list of instance specific settings. These can be accessed within
  // the instanceSettingsForm.  When the instanceSettingsForm is submitted
  // then Drupal will automatically change these settings for the instance.
  // It is recommended to put settings at the instance level whenever possible.
  // If you override this variable in a child class be sure to replicate the
  // term_name, term_vocab, term_accession and term_fixed keys as these are
  // required for all TripalFields.
  public static $default_instance_settings = [
    // The short name for the vocabulary (e.g. schema, SO, GO, PATO, etc.).
    'term_vocabulary' => 'data',
    // The name of the term.
    'term_name' => 'Map',
    // The unique ID (i.e. accession) of the term.
    'term_accession' => '1274',
    // Set to TRUE if the site admin is allowed to change the term
    // type. This will create form elements when editing the field instance
    // to allow the site admin to change the term settings above.
    'term_fixed' => FALSE,
  ];

  // The default widget for this field.
  public static $default_widget = 'chado_linker__featuremap_widget';

  // The default formatter for this field.
  public static $default_formatter = 'chado_linker__featuremap_formatter';

  // --------------------------------------------------------------------------
  //              PROTECTED CLASS MEMBERS -- DO NOT OVERRIDE
  // --------------------------------------------------------------------------
  // An array containing details about the field. The format of this array
  // is the same as that returned by field_info_fields()
  protected $field;

  // An array containing details about an instance of the field. A field does
  // not have to have an instance.  But if dealing with an instance (such as
  // when using the widgetForm, formatterSettingsForm, etc.) it should be set.
  protected $instance;


  /**
   * @see TripalField::elements()
   */
  public function elementInfo() {

    $field_term = $this->getFieldTermID();
    $unittype_term = chado_get_semweb_term('featuremap', 'unittype_id');
    $name_term = chado_get_semweb_term('featuremap', 'name');
    $description_term = chado_get_semweb_term('featuremap', 'description');

    return [
      $field_term => [
        'operations' => ['eq', 'contains', 'starts'],
        'sortable' => TRUE,
        'searchable' => TRUE,
        'type' => 'xs:complexType',
        'readonly' => FALSE,
        'elements' => [
          $unittype_term => [
            'searchable' => TRUE,
            'label' => 'Featuremap Units',
            'help' => 'The units used by the featuremap',
            'operations' => ['eq', 'ne', 'contains', 'starts'],
            'sortable' => TRUE,
            'type' => 'xs:string',
            'readonly' => FALSE,
            'required' => TRUE,
          ],
          $name_term => [
            'searchable' => TRUE,
            'label' => 'Featuremap Name',
            'help' => 'The name of the featuremap.',
            'operations' => ['eq', 'ne', 'contains', 'starts'],
            'sortable' => TRUE,
            'type' => 'xs:string',
            'readonly' => FALSE,
            'required' => TRUE,
          ],
          $description_term => [
            'searchable' => TRUE,
            'label' => 'Featuremap Description',
            'help' => 'A description of the featuremap.',
            'operations' => ['contains'],
            'sortable' => TRUE,
            'type' => 'xs:string',
            'readonly' => TRUE,
            'required' => FALSE,
          ],
          'entity' => [
            'searchable' => FALSE,
          ],
        ],
      ],
    ];
  }

  /**
   *
   * @see TripalField::load()
   */
  public function load($entity) {

    $record = $entity->chado_record;

    $field_name = $this->field['field_name'];
    $field_type = $this->field['type'];
    $field_table = $this->instance['settings']['chado_table'];
    $field_column = $this->instance['settings']['chado_column'];
    $base_table = $this->instance['settings']['base_table'];

    $unittype_term = chado_get_semweb_term('featuremap', 'unittype_id');
    $name_term = chado_get_semweb_term('featuremap', 'name');
    $description_term = chado_get_semweb_term('featuremap', 'description');
    $summary_term = 'NCIT:C25463'; // ncit:Count

    // Set some defaults for the empty record.
    $entity->{$field_name}['und'][0] = [
      'value' => [],
    ];

    // Get the FK that links to the base record.
    $schema = chado_get_schema($field_table);
    $pkey = $schema['primary key'][0];
    if (!isset($schema['foreign keys'][$base_table]['columns'])) {
      return;
    }
    $fkey_lcolumn = key($schema['foreign keys'][$base_table]['columns']);
    $fkey_rcolumn = $schema['foreign keys'][$base_table]['columns'][$fkey_lcolumn];

    // If we don't have a chado record, return before creating a stub for this field!
    if (!$record) {
      return;
    }

    // Linker table name may have featuremap as either prefix or suffix
    $linker_table = $base_table . '_featuremap';
    if (!chado_table_exists($linker_table)) {
      $linker_table = 'featuremap_' . $base_table;
    }
    if (!chado_table_exists($linker_table)) {
      return;
    }

    // Evaluate how many linked records there are, and if too many just show a summary.
    $chado_linker_field_max_delta = variable_get('chado_linker_field_max_delta', 200);
    if (array_key_exists('chado_linker_field_max_delta', $this->instance['settings'])) {
      $chado_linker_field_max_delta = $this->instance['settings']['chado_linker_field_max_delta'];
    }
    $sql1 = 'SELECT COUNT(*) FROM {'.$linker_table.'} WHERE '.$fkey_lcolumn.' = :fkey_lcolumn_id';
    $args1 = [':fkey_lcolumn_id' => $record->$fkey_lcolumn];
    $count = chado_query($sql1, $args1)->fetchField();

    if ($count <= $chado_linker_field_max_delta) {
      // Handle type_id and rank only when they exist in the linker table.
      $type_sql = '';
      if (chado_column_exists($linker_table, 'type_id')) {
        $type_sql .= ' LT.type_id AS linker_type_id,';
      }
      if (chado_column_exists($linker_table, 'rank')) {
        $type_sql .= ' LT.rank AS linker_rank,';
      }
      // Since there could be many records, perform SQL query directly to reduce overhead.
      $sql2 = 'SELECT LT.'.$pkey.' AS pkey_value,'
            . $type_sql
            . ' FM.featuremap_id, FM.name, FM.description,'
            . ' T.name AS type, LOWER(T.name) AS sortkey'
            . ' FROM {'.$linker_table.'} LT'
            . ' LEFT JOIN {featuremap} FM ON LT.featuremap_id = FM.featuremap_id'
            . ' LEFT JOIN {cvterm} T ON FM.unittype_id = T.cvterm_id'
            . ' WHERE LT.'.$fkey_lcolumn.' = :fkey_lcolumn_id'
            . ' ORDER BY sortkey, LOWER(FM.name)';
      $args2 = [':fkey_lcolumn_id' => $record->$fkey_lcolumn];
      $linkers = chado_query($sql2, $args2);

      $i = 0;
      while ( $linker = $linkers->fetchObject() ) {
        $entity->{$field_name}['und'][$i] = [
          'value' => [
            $unittype_term => $linker->type,
            $name_term => $linker->name,
            $description_term => $linker->description,
          ],
          // Add elements that are not part of the values but used by
          // the chado storage back-end for saving values.
          'chado-' . $field_table . '__' . $pkey => $linker->pkey_value,
          'chado-' . $field_table . '__' . $fkey_lcolumn => $record->$fkey_lcolumn,
          'chado-' . $field_table . '__' . 'featuremap_id' => $linker->featuremap_id,
          // For the widget to work properly we will preform values.
          'featuremap_name' => $linker->name . ' [id: ' . $linker->featuremap_id . ']',
        ];
        if (property_exists($linker, 'linker_type_id')) {
          $entity->{$field_name}['und'][$i]['chado-' . $field_table . '__type_id'] = $linker->linker_type_id;
        }
        if (property_exists($linker, 'linker_rank')) {
          $entity->{$field_name}['und'][$i]['chado-' . $field_table . '__rank'] = $linker->linker_rank;
        }
        $entity_id = chado_get_record_entity_by_table('featuremap', $linker->featuremap_id);
        if ($entity_id) {
          $entity->{$field_name}['und'][$i]['value']['entity'] = 'TripalEntity:' . $entity_id;
        }
        $i++;
      }
    }
    else {
      // If too many records to display, just return a summary. The widget won't
      // show any existing records, but can be used to add additional records.
      // Web services will only show this summary.
      $sql3 = 'SELECT DISTINCT FM.name, LOWER(FM.name) AS sortkey, COUNT(*) AS count'
            . ' FROM {'.$linker_table.'} LT'
            . ' LEFT JOIN {featuremap} FM ON LT.featuremap_id = FM.featuremap_id'
            . ' LEFT JOIN {cvterm} T ON FM.unittype_id = T.cvterm_id'
            . ' WHERE LT.'.$fkey_lcolumn.' = :fkey_lcolumn_id'
            . ' GROUP BY T.name'
            . ' ORDER BY sortkey';
      $args3 = [':fkey_lcolumn_id' => $record->$fkey_lcolumn];
      $featuremaptypes = chado_query($sql3, $args3);

      // Summarize each featuremap unittype separately.
      $content = '';
      $ntypes = 0;
      while ( $featuremaptype = $featuremaptypes->fetchObject() ) {
        $content .= format_plural($featuremaptype->count,
                      'There is :count :type featuremap<br>',
                      'There are :count :type featuremaps<br>',
                      [':count' => $featuremaptype->count, ':type' => $featuremaptype->name]);
        $ntypes++;
      }
      if ($ntypes > 1) {
        $content .= t('Total: :count', [':count' => $count]);
      }

      // The formatter will check for the $summary_term key, and when
      // present will display this summary and not display the usual table.
      $entity->{$field_name}['und'][0] = [
        'value' => [
          $summary_term => $content,
        ],
      ];
    }
  }
}


/**
 * An Ajax callback for the widget.
 */
function chado_linker__featuremap_widget_form_ajax_callback($form, $form_state) {

  $field_name = $form_state['triggering_element']['#parents'][0];
  $delta = $form_state['triggering_element']['#parents'][2];

  return $form[$field_name]['und'][$delta];
}

/**
 * Theme function for the widget.
 *
 * @param $variables
 */
function theme_chado_linker__featuremap_widget($variables) {
  $element = $variables['element'];

  // These two fields were added to the widget to help identify the fields
  // for layout.
  $table_name = $element['#table_name'];
  $fkey = $element['#fkey_field'];

  $layout = "
      <div class=\"chado-linker--featuremap-widget\">
        <div class=\"chado-linker--featuremap-widget-item\">" .
    drupal_render($element['name']) . "
        </div>
      </div>
    ";

  return $layout;
}
