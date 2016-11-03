<?php
/**
 * @fle
 * Schema.org type definitions.
 */

/**
 * Returns Schema.org types and their particularities.
 *
 * @return array
 *   Returns a single type if requested, or all schemas, if not.
 */
function structured_data_get_schemas($type = NULL) {
  $schemas = array(
    'Article' => array(
      'name' => t('Article'),
      'required' => array(
        'headline' => array(
          'name' => 'Headline',
          'description' => 'Headlines should not exceed 110 characters.',
          'type' => 'text',
        ),
        'image' => array(
          'name' => 'Image',
          'description' => 'Images should be at least 696 pixels wide.',
          'type' => 'ImageObject',
        ),
        'publisher' => array(
          'name' => 'Publisher',
          'description' => 'The publisher of the article.',
          'type' => 'Organization',
        ),
        'datePublished' => array(
          'name' => 'Date published',
          'description' => 'The date and time the article was first published',
          'type' => 'DateTime',
        ),
        'author' => array(
          'name' => 'Author',
          'description' => 'The author of the article.',
          'type' => 'Person',
        ),
      ),
      'recommended' => array(
        'description' => array(
          'name' => 'Description',
          'description' => 'A short description of the article.',
          'type' => 'text',
        ),
      ),
    ),
    'BlogPosting' => array(
      'name' => t('Blog Posting'),
      'required' => array(
        'headline' => array(
          'name' => 'Headline',
          'description' => 'Headlines should not exceed 110 characters.',
          'type' => 'text',
        ),
        'image' => array(
          'name' => 'Image',
          'description' => 'Images should be at least 696 pixels wide.',
          'type' => 'ImageObject',
        ),
        'publisher' => array(
          'name' => 'Publisher',
          'description' => 'The publisher of the article.',
          'type' => 'Organization',
        ),
        'datePublished' => array(
          'name' => 'Date published',
          'description' => 'The date and time the article was first published',
          'type' => 'DateTime',
        ),
        'author' => array(
          'name' => 'Author',
          'description' => 'The author of the article.',
          'type' => 'Person',
        ),
      ),
    ),
    'NewsArticle' => array(
      'name' => t('News Article'),
      'required' => array(
        'headline' => array(
          'name' => 'Headline',
          'description' => 'Headlines should not exceed 110 characters.',
          'type' => 'text',
        ),
        'image' => array(
          'name' => 'Image',
          'description' => 'Images should be at least 696 pixels wide.',
          'type' => 'ImageObject',
        ),
        'publisher' => array(
          'name' => 'Publisher',
          'description' => 'The publisher of the article.',
          'type' => 'Organization',
        ),
        'datePublished' => array(
          'name' => 'Date published',
          'description' => 'The date and time the article was first published',
          'type' => 'DateTime',
        ),
        'author' => array(
          'name' => 'Author',
          'description' => 'The author of the article.',
          'type' => 'Person',
        ),
      ),
    ),
    'Organization' => array(
      'name' => t('Organization'),
      'required' => array(),
      'hidden' => TRUE,
    ),
    'Person' => array(
      'name' => t('Person'),
      'required' => array(),
      'hidden' => TRUE,
    ),
    'VideoObject' => array(
      'name' => t('Video'),
      'required' => array(
        'name',
        'description',
        'thumbnailUrl',
        'publisher',
      ),
    ),
  );

  // Allow schemas to be altered.
  drupal_alter('structured_data_schemas', $schemas);

  if ($type == NULL) {
    return $schemas;
  }
  else {
    return $schemas[$type];
  }
}
