<?php
/**
 * @file
 * Contains functions for administration of chado linker field settings.
 *
 */

/**
 * Provides the field settings form.
 */
function chado_linker_field_settings_admin_form($form, $form_state) {

  $form['general'] = [
    '#type' => 'fieldset',
    '#title' => 'Linker Field Display Options'
  ];

  $form['general']['chado_linker_field_max_delta']= [
    '#type' => 'textfield',
    '#title' => t('Maximum records to display'),
    '#size' => 20,
    '#description' => t('This option controls the maximum number of records'
       . ' to display in a linker field. If more than this number of records'
       . ' are stored in chado, the field will display a summary view.'),
    '#default_value' => variable_get('chado_linker_field_max_delta', 200),
  ];

  $form['general']['chado_linker_field_max_height']= [
    '#type' => 'textfield',
    '#title' => t('Maximum field height'),
    '#size' => 20,
    '#description' => t('For fields that support it, this option sets the'
       . ' maximium height of a single record. If it is taller, then a'
       . ' scrollbar is added.'),
    '#default_value' => variable_get('chado_linker_field_max_height', 200),
  ];

  $form['submit'] = [
    '#type' => 'submit',
    '#value' => 'Save Configuration'
  ];

  return $form;
}

/**
 * Validate the field settings form.
 */
function chado_linker_field_settings_admin_form_validate($form, &$form_state) {

  // Validation for the positive integer fields.
  $fields = ['chado_linker_field_max_delta', 'chado_linker_field_max_height'];
  foreach ($fields as $field) {
    $value = $form_state['values'][$field];
    if (!preg_match('/^\d+$/', $value) or ($value < 1)) {
      form_set_error($field, 'Please enter a positive integer.');
    }
  }
}

/**
 * Submit the field settings form.
 */
function chado_linker_field_settings_admin_form_submit($form, $form_state) {

  variable_set('chado_linker_field_max_delta', $form_state['values']['chado_linker_field_max_delta']);
  variable_set('chado_linker_field_max_height', $form_state['values']['chado_linker_field_max_height']);
}
