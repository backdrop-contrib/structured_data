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

  $form['local'] = array(
    '#type' => 'fieldset',
    '#title' => t('Local business details'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
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
  $form['local']['structured_data_phone'] = array(
    '#type' =>'textfield',
    '#title' => t('Phone'),
    '#default_value' => variable_get('structured_data_phone', ''),
  );

  $form = system_settings_form($form);

  return $form;
}

/**
 * Submit handler for structured_data_settings_form().
 */
function structured_data_settings_form_submit($form, &$form_state) {
  global $user;
  unset($form['structured_data_site_logo_current']);
  $form['structured_data_site_logo_custom']['#file']->status = FILE_STATUS_PERMANENT;
  $file = file_save($form['structured_data_site_logo_custom']['#file']);
  file_usage_add($file, 'structured_data', 'site_logo', $user->uid);
}
