<?php
/**
 * @file
 * Administrative pages for the structured_data module.
 */

/**
 * Form callback for admin settings page.
 */
function structured_data_settings_form() {
  $config = config('structured_data.settings');
  $form['#config'] = 'structured_data.settings';

  $site_name = config_get('system.core', 'site_name');
  $form['marketing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Marketing details'),
    '#collapsible' => TRUE,
  );
  $form['marketing']['site_name_custom'] = array(
    '#type' =>'textfield',
    '#title' => t('Official site name'),
    '#description' => t('Site name or Company name, must be reasonably similar to your domain name.'),
    '#default_value' => $config->get('site_name_custom'),
    '#attributes' => array('placeholder' => check_plain($site_name)),
  );
  $form['marketing']['site_name_alternative'] = array(
    '#type' =>'textfield',
    '#title' => t('Alternate name for Search Engines to consider'),
    '#default_value' => $config->get('site_name_alternative', ''),
  );

  $logo_info = structured_data_get_site_logo();
  if ($logo_info['width'] > 600 || $logo_info['height'] > 60) {
    $problem_width = 'a width greater than 600px';
    $problem_height = 'a height greater than 60px';
    $problem_both = $problem_width . ' or ' . $problem_height;

    if ($logo_info['width'] > 600 && $logo_info['height'] > 60) {
      $problem = $problem_both;
    }
    else {
      if (isset($logo_info['width']) && $logo_info['width'] > 600) {
        $problem = $problem_width;
      }
      elseif (isset($logo_info['height']) && $logo_info['height'] > 60) {
        $problem = $problem_height;
      }
    }
    drupal_set_message(t('Logos with !problem will be rejected by Google.', array('!problem' => $problem)), 'warning');
  }

  $form['marketing']['site_logo_custom'] = array(
    '#type' => 'managed_file',
    '#title' => t('Alternate Logo'),
    '#description' => t('Allowed extensions: jpg, jpeg, png, gif.'),
    '#upload_location' => 'public://structured_data/',
    '#default_value' => $config->get('site_logo_custom', ''),
    '#upload_location' => 'public://',
    '#upload_validators' => array(
      'file_validate_extensions' => array('gif png jpg jpeg'),
      'file_validate_image_resolution' => array('600x60'),
    ),
  );
  $default = '';
  if (isset($logo_info['path'])) {
    $default = theme('image', array('path' => $logo_info['path']));
  }
  $form['marketing']['site_logo_current'] = array(
    '#type' =>'item',
    '#title' => t('Current Logo'),
    '#markup' => $default,
    '#description' => t('Logos should be exactly 60px tall with a width of 600px or less. '),
  );

  // Node Type filter.
  $form['nodes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content types'),
    '#description' => t('Enable Rich Snippets for the following content types.'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $link_options = array('query' => array('destination' => 'admin/config/metadata/structured-data'));

  $type_rows = array();
  $type_defaults = array();
  $allowed_types = config_get('structured_data.settings', 'node_types');
  // @todo remove pathless nodes.
  foreach (node_type_get_types() as $type) {
    if ($allowed_types[$type->type]) {
      $type_defaults[$type->type] = $type->type;
      $type_rows[$type->type] = array(
        'type' => t($type->name),
        'content' => structured_data_get_node_type_config($type->type),
        'link' => l(t('Configure'), 'admin/structure/types/manage/' . $type->type . '/configure', $link_options),
      );
    }
    else {
      $type_rows[$type->type] = array(
        'type' => t($type->name),
        'content' => NULL,
        'link' => NULL,
      );
    }
  }

  // Set the table select.
  $form['nodes']['node_types'] = array(
    '#title' => t('Node Types'),
    '#type' => 'tableselect',
    '#header' => array(
      'type' => t('Content Type'),
      'content' => t('Rich snippet settings'),
      'link' => t('Configure'),
    ),
    '#options' => $type_rows,
    '#default_value' => $config->get('node_types', $type_defaults),
    '#empty' => t('No Content Types.'),
  );

  $form['corporate'] = array(
    '#type' => 'fieldset',
    '#title' => t('Corporate contact details'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['corporate']['phone'] = array(
    '#type' =>'textfield',
    '#title' => t('Phone number'),
    '#default_value' => $config->get('phone', ''),
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
  $form['corporate']['phone_type'] = array(
    '#type' => 'select',
    '#title' => t('Contact type'),
    '#options' => $contact_types,
    '#empty_option' => t('- None - '),
    '#default_value' => $config->get('phone_type', ''),
  );
  $form['corporate']['phone_options'] = array(
    '#type' => 'checkboxes',
    '#title' => t('About this line'),
    '#options' => array(
      'TollFree' => t('Toll free'),
      'HearingImpairedSupported' => t('Serves the hearing-impaired'),
    ),
    '#default_value' => $config->get('phone_options', ''),
  );
  // @todo Add area served, list all/common country codes?

  $form['local'] = array(
    '#type' => 'fieldset',
    '#title' => t('Local business details'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['local']['business_type'] = array(
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
    '#default_value' => $config->get('business_type', ''),
  );
  // Address fields.
  $form['local']['address'] = array(
    '#type' =>'textfield',
    '#title' => t('Address'),
    '#size' => 120,
    '#default_value' => $config->get('address', ''),
  );
  $form['local']['city'] = array(
    '#type' =>'textfield',
    '#title' => t('City'),
    '#default_value' => $config->get('city', ''),
  );
  $form['local']['state'] = array(
    '#type' =>'textfield',
    '#title' => t('State'),
    '#default_value' => $config->get('state', ''),
  );
  $form['local']['zip'] = array(
    '#type' =>'textfield',
    '#title' => t('Zip'),
    '#default_value' => $config->get('zip', ''),
  );

  return system_settings_form($form);
}

/**
 * Submit handler for structured_data_settings_form().
 */
function structured_data_settings_form_submit($form, &$form_state) {
  // Create a file usage record for the logo file uploaded.
  $form['site_logo_custom']['#file']->status = FILE_STATUS_PERMANENT;
  $file = file_save($form['site_logo_custom']['#file']);
  global $user;
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
  $structured_data = config_get('node.type.' . $type, 'structured_data');
  if (isset($structured_data['schema'])) {
    $output = t('Schema.org data type: %schema.',
      array('%schema' => $structured_data['schema']));
  }
  else {
    $output = 'Not configured.';
  }

  return $output;
}
