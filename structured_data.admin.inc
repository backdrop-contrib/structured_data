<?php

/**
 * Implements hook_form().
 */
function structured_data_admin_site_name_settings() {
  $form['structured_data_site_name_default'] = array(
    '#type' =>'checkbox',
    '#title' => t('Use the default site name'),
    '#default_value' => variable_get('structured_data_site_name_default', TRUE),
  );

  $form['structured_data_site_name_custom'] = array(
    '#type' =>'textfield',
    '#title' => t('Custom site name'),
    '#default_value' => variable_get('structured_data_site_name_custom', ''),
    '#states' => array(
      'visible' => array(
        ':input[name="structured_data_site_name_default"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['structured_data_site_name_alternative'] = array(
    '#type' =>'textfield',
    '#title' => t('Alternative site name'),
    '#default_value' => variable_get('structured_data_site_name_alternative', ''),
  );

  return system_settings_form($form);
}

