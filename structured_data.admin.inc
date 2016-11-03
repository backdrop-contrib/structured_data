<?php
/**
 * @file
 * Administrative pages for the structured_data module.
 */

/**
 * Form callback for admin settings page.
 */
function structured_data_settings_form() {
  $site_name = variable_get('site_name', '');
  $form['marketing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Marketing details'),
    '#collapsible' => TRUE,
  );
  $form['marketing']['structured_data_site_name_custom'] = array(
    '#type' =>'textfield',
    '#title' => t('Official site name'),
    '#description' => t('Site name or Company name, must be reasonably similar to your domain name. If left blank, %name will be used.', array('%name' => $site_name)),
    '#default_value' => variable_get('structured_data_site_name_custom', ''),
    '#attributes' => array('placeholder' => check_plain($site_name)),
  );
  $form['marketing']['structured_data_site_name_alternative'] = array(
    '#type' =>'textfield',
    '#title' => t('Alternative site name (optional)'),
    '#description' => t('An alternate name you want Search Engines to consider.'),
    '#default_value' => variable_get('structured_data_site_name_alternative', ''),
  );

  $logo_data = structured_data_get_site_logo_info();
  $logo_info = getimagesize($logo_data['path']);
  $data['width'] = $logo_info[0];
  $data['height'] = $logo_info[1];

  if ($logo_info['width'] > 600 || $logo_info['height'] > 60) {
    $problem_width = 'a width greater than 600px';
    $problem_height = 'a height greater than 60px';
    $problem_both = $problem_width . ' or ' . $problem_height;

    if ($logo_info['width'] > 600 && $logo_info['height'] > 60) {
      $problem = $problem_both;
    }
    else {
      if ($logo_info['width'] > 600) {
        $problem = $problem_width;
      }
      elseif ($logo_info['height'] > 60) {
        $problem = $problem_height;
      }
    }
    drupal_set_message(t('Logos with !problem will be rejected by Google.', array('!problem' => $problem)), 'warning');
  }
  $form['marketing']['structured_data_site_logo_current'] = array(
    '#type' =>'item',
    '#title' => t('Image that will be presented to search engines as your logo:'),
    '#markup' => theme('image', array('path' => $logo_data['path'])),
  );
  $form['marketing']['structured_data_site_logo_custom'] = array(
    '#type' => 'managed_file',
    '#title' => t('Custom site logo'),
    '#description' => t('Logos should be exactly 60px tall with width <= 600px. Allowed extensions: jpg, jpeg, png, gif.'),
    '#upload_location' => 'public://structured_data/',
    '#default_value' => variable_get('structured_data_site_logo_custom', ''),
    '#upload_location' => 'public://',
    '#upload_validators' => array(
      'file_validate_extensions' => array('gif png jpg jpeg'),
      'file_validate_image_resolution' => array('600x60'),
    ),
  );

  $form['corporate'] = array(
    '#type' => 'fieldset',
    '#title' => t('Corporate contact details'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['corporate']['structured_data_phone'] = array(
    '#type' =>'textfield',
    '#title' => t('Phone number'),
    '#default_value' => variable_get('structured_data_phone', ''),
  );
  $contact_types = array(
    'customer service' => t('customer service'),
    'technical support' => t('technical support'),
    'billing support' => t('billing support'),
    'bill payment' => t('bill payment'),
    'sales' => t('sales'),
    'reservations' => t('reservations'),
    'credit card support' => t('credit card support'),
    'emergency' => t('emergency'),
    'baggage tracking' => t('baggage tracking'),
    'roadside assistance' => t('roadside assistance'),
    'package tracking' => t('package tracking'),
  );
  $form['corporate']['structured_data_phone_type'] = array(
    '#type' => 'select',
    '#title' => t('Contact type'),
    '#options' => $contact_types,
    '#empty_option' => t('- None - '),
    '#default_value' => variable_get('structured_data_phone_type', ''),
  );
  $form['corporate']['structured_data_phone_options'] = array(
    '#type' => 'checkboxes',
    '#title' => t('About this line'),
    '#options' => array(
      'TollFree' => t('Toll free'),
      'HearingImpairedSupported' => t('Serves the hearing-impaired'),
    ),
    '#default_value' => variable_get('structured_data_phone_options', ''),
  );
  // @todo Add area served, list all/common country codes?

  $form['local'] = array(
    '#type' => 'fieldset',
    '#title' => t('Local business details'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['local']['structured_data_business_type'] = array(
    '#type' => 'select',
    '#title' => t('Type of business'),
    '#options' => array(
      'Organization' => 'Organization',
      'Airline' => 'Airline',
      'Corporation' => 'Corporation',
      'GeneralContractor' => 'General Contractor',
      'EducationalOrganization' => 'Educational Organization',
      'GovernmentOrganization' => 'Government Organization',
      'LocalBusiness' => 'Local Business',
      'MedicalOrganization' => 'Medical Organization',
      'NGO' => 'NGO',
      'PerformingGroup' => 'Performing Group',
      'SportsOrganization' => 'Sports Organization',
    ),
    '#empty_option' => t('- None - '),
    '#default_value' => variable_get('structured_data_business_type', ''),
  );
  // Address fields.
  $form['local']['structured_data_address'] = array(
    '#type' =>'textfield',
    '#title' => t('Address'),
    '#size' => 120,
    '#default_value' => variable_get('structured_data_address', ''),
  );
  $form['local']['structured_data_city'] = array(
    '#type' =>'textfield',
    '#title' => t('City'),
    '#default_value' => variable_get('structured_data_city', ''),
  );
  $form['local']['structured_data_state'] = array(
    '#type' =>'textfield',
    '#title' => t('State'),
    '#default_value' => variable_get('structured_data_state', ''),
  );
  $form['local']['structured_data_zip'] = array(
    '#type' =>'textfield',
    '#title' => t('Zip'),
    '#default_value' => variable_get('structured_data_zip', ''),
  );

  // Node Type filter.
  $form['nodes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content types'),
    '#description' => t('Enable Rich Snippets for the following content types.'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $type_rows = array();
  $type_defaults = array();
  foreach (node_type_get_types() as $type) {
    $type_defaults[$type->type] = $type->type;
    $type_rows[$type->type] = array(
      'type' => t($type->name),
      'content' => structured_data_get_node_type_config($type->type),
      'link' => l(t('Configure'), 'admin/structure/types/manage/' . $type->type . '/configure'),
    );
  }

  // Set the table select.
  $form['nodes']['structured_data_node_types'] = array(
    '#title' => t('Node Types'),
    '#type' => 'tableselect',
    '#header' => array(
      'type' => t('Content Type'),
      'content' => t('Current rich snippet settings'),
      'link' => t('Configure'),
    ),
    '#options' => $type_rows,
    '#default_value' => variable_get('structured_data_node_types', $type_defaults),
    '#empty' => t('No Content Types.'),
  );

  $form = system_settings_form($form);

  return $form;
}

/**
 * Submit handler for structured_data_settings_form().
 */
function structured_data_settings_form_submit($form, &$form_state) {
  // Create a file usage record for the logo file uploaded.
  global $user;
  $form['structured_data_site_logo_custom']['#file']->status = FILE_STATUS_PERMANENT;
  $file = file_save($form['structured_data_site_logo_custom']['#file']);
  file_usage_add($file, 'structured_data', 'site_logo', $user->uid);
}

/**
 * Helper function: Gets info about how the node type is configured for the
 *   administration page. Should include schema.org type and fields.
 *
 * @param $type
 *   Node type for configuration retrieved.
 */
function structured_data_get_node_type_config($type) {
  if ($schema = variable_get('structured_data_schema_' . $type, FALSE)) {
    $output = t('Schema.org type: %schema.', array('%schema' => $schema));
  }
  else {
    $output = 'Not configured.';
  }

  return $output;
}
