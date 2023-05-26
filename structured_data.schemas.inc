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
// Article
    'Article' => array(
      'name' => t('Article'),
      'properties' => array(
        'headline' => array(
          'name' => 'Headline',
          'description' => 'Headlines should not exceed 110 characters.',
          'type' => array('Text'),
          'required' => TRUE,
        ),
        'image' => array(
          'name' => 'Image',
          'description' => 'Images should be at least 696 pixels wide.',
          'type' => array('ImageObject'),
          'required' => TRUE,
        ),
        'datePublished' => array(
          'name' => 'Date published',
          'description' => 'The date and time the article was first published',
          'type' => array('DateTime'),
          'required' => TRUE,
        ),
        'dateModified' => array(
          'name' => 'Date modified',
          'description' => 'The date and time the article was most recently modified',
          'type' => array('DateTime'),
        ),
        'author' => array(
          'name' => 'Author',
          'description' => 'The author of the article.',
          'type' => array('Person'),
          'required' => TRUE,
        ),
        'description' => array(
          'name' => 'Description',
          'description' => 'A short description of the article.',
          'type' => array('Text'),
        ),
        'publisher' => array(
          'name' => 'Publisher',
          'description' => 'The publisher of the article.',
          'type' => array('Organization'),
          'required' => TRUE,
        ),
      ),
    ),
// BlogPosting
    'BlogPosting' => array(
      'name' => t('Blog Posting'),
      'properties' => array(
        'headline' => array(
          'name' => 'Headline',
          'description' => 'Headlines should not exceed 110 characters.',
          'type' => array('Text'),
          'required' => TRUE,
        ),
        'image' => array(
          'name' => 'Image',
          'description' => 'Images should be at least 696 pixels wide.',
          'type' => array('ImageObject'),
          'required' => TRUE,
        ),
        'datePublished' => array(
          'name' => 'Date published',
          'description' => 'The date and time the article was first published',
          'type' => array('DateTime'),
          'required' => TRUE,
        ),
        'dateModified' => array(
          'name' => 'Date modified',
          'description' => 'The date and time the article was most recently modified',
          'type' => array('DateTime'),
        ),
        'author' => array(
          'name' => 'Author',
          'description' => 'The author of the article.',
          'type' => array('Person'),
          'required' => TRUE,
        ),
        'description' => array(
          'name' => 'Description',
          'description' => 'A short description of the article.',
          'type' => array('Text'),
        ),
        'publisher' => array(
          'name' => 'Publisher',
          'description' => 'The publisher of the article.',
          'type' => array('Organization'),
          'required' => TRUE,
        ),
      ),
    ),
// NewsArticle
    'NewsArticle' => array(
      'name' => t('News Article'),
      'properties' => array(
        'headline' => array(
          'name' => 'Headline',
          'description' => 'Headlines should not exceed 110 characters.',
          'type' => array('Text'),
          'required' => TRUE,
        ),
        'image' => array(
          'name' => 'Image',
          'description' => 'Images should be at least 696 pixels wide.',
          'type' => array('ImageObject'),
          'required' => TRUE,
        ),
        'datePublished' => array(
          'name' => 'Date published',
          'description' => 'The date and time the article was first published',
          'type' => array('DateTime'),
          'required' => TRUE,
        ),
        'author' => array(
          'name' => 'Author',
          'description' => 'The author of the article.',
          'type' => array('Person'),
          'required' => TRUE,
        ),
        'description' => array(
          'name' => 'Description',
          'description' => 'A short description of the article.',
          'type' => array('Text'),
        ),
        'dateModified' => array(
          'name' => 'Date modified',
          'description' => 'The date and time the article was most recently modified',
          'type' => array('DateTime'),
        ),
        'publisher' => array(
          'name' => 'Publisher',
          'description' => 'The publisher of the article.',
          'type' => array('Organization'),
          'required' => TRUE,
        ),
      ),
    ),
// Recipe
    'Recipe' => array(
      'name' => t('Recipe'),
      'properties' => array(
        'name' => array(
          'name' => 'Name',
          'description' => 'The name of the recipe.',
          'type' => array('Text'),
          'required' => TRUE,
        ),
        'datePublished' => array(
          'name' => 'Date published',
          'description' => 'The date and time the recipe was first published',
          'type' => array('DateTime'),
          'required' => TRUE,
        ),
        'dateModified' => array(
          'name' => 'Date modified',
          'description' => 'The date and time the article was most recently modified',
          'type' => array('DateTime'),
        ),
        'image' => array(
          'name' => 'Image',
          'description' => 'Images should be at least 696 pixels wide.',
          'type' => array('ImageObject'),
        ),
        'video' => array(
          'name' => 'Video',
          'description' => 'An embedded video object or a video file.',
          'type' => array('VideoObject'),
        ),
        'description' => array(
          'name' => 'Description',
          'description' => 'A description of the recipe.',
          'type' => array('Text'),
        ),
        'author' => array(
          'name' => 'Author',
          'description' => 'The author of the recipe.',
          'type' => array('Person'),
        ),
        'prepTime' => array(
          'name' => 'Prep Time',
          'description' => 'The length of time it takes to prepare the items to be used in instructions or a direction, in ISO 8601 duration format.',
          'type' => array('Duration'),
        ),
        'cookTime' => array(
          'name' => 'Cook Time',
          'description' => 'The time it takes to actually cook the dish, in ISO 8601 duration format.',
          'type' => array('Duration'),
        ),
        'totalTime' => array(
          'name' => 'Total Time',
          'description' => 'The total time required to perform instructions or a direction (including time to prepare the supplies), in ISO 8601 duration format.',
          'type' => array('Duration'),
        ),
        'keywords' => array(
          'name' => 'Keywords',
          'description' => 'Keywords or tags used to describe this content. Multiple entries in a keywords list are typically delimited by commas.',
          'type' => array('Text'),
        ),
        'recipeCategory' => array(
          'name' => 'Recipe Category',
          'description' => 'The category of the recipe—for example, appetizer, entree, etc.',
          'type' => array('Text'),
        ),
        'recipeCuisine' => array(
          'name' => 'Recipe Cuisine',
          'description' => 'The cuisine of the recipe (for example, French or Ethiopian).',
          'type' => array('Text'),
        ),
        'cookingMethod' => array(
          'name' => 'Cooking Method',
          'description' => 'The method of cooking, such as Frying, Steaming, ...',
          'type' => array('Text'),
        ),
        'recipeIngredient' => array(
          'name' => 'Recipe Ingredient',
          'description' => 'A single ingredient used in the recipe, e.g. sugar, flour or garlic.',
          'type' => array('Text'),
        ),
        'recipeInstructions' => array(
          'name' => 'Recipe Instructions',
          'description' => 'A step in making the recipe, in the form of a single item (document, video, etc.) or an ordered list with HowToStep and/or HowToSection items.',
          'type' => array('Text', 'ItemList', 'CreativeWork'),
        ),
        'aggregateRating' => array(
          'name' => 'AggregateRating',
          'description' => 'The overall rating, based on a collection of reviews or ratings, of the item.',
          'type' => array('AggregateRating'),
        ),
        'recipeYield' => array(
          'name' => 'Recipe Yield',
          'description' => 'The quantity produced by the recipe (for example, number of people served, number of servings, etc).',
          'type' => array('QuantitativeValue', 'Text'),
          'hidden' => TRUE,
        ),
        'suitableForDiet' => array(
          'name' => 'Suitable For Diet',
          'description' => 'Indicates a dietary restriction or guideline for which this recipe or menu item is suitable, e.g. diabetic, halal etc.',
          'type' => array('RestrictedDiet'),
          'hidden' => TRUE,
        ),
        'nutrition' => array(
          'name' => 'Nutrition Information',
          'description' => 'Nutrition information about the recipe or menu item.',
          'type' => array('NutritionInformation'),
          'hidden' => TRUE,
        ),
        'publisher' => array(
          'name' => 'Publisher',
          'description' => 'The publisher of the recipe.',
          'type' => array('Organization'),
        ),
      ),
    ),
// Review
    'Review' => array(
      'name' => t('Review'),
      'properties' => array(
        'name' => array(
          'name' => 'Name',
          'description' => 'The name of the item being reviewed.',
          'type' => array('Text'),
          'required' => TRUE,
        ),
        'itemReviewed' => array(
          'name' => 'itemReviewed',
          'type' => array('Thing'),
          'description' => 'The item that is being reviewed/rated.',
        ),
        'description' => array(
          'name' => 'Description',
          'description' => 'A description of the item being reviewed.',
          'type' => array('Text'),
        ),
        'reviewBody' => array(
          'name' => 'Review',
          'description' => 'The actual body of the review.',
          'type' => array('Text'),
          'required' => TRUE,
        ),
        'reviewRating' => array(
          'name' => 'Review Rating',
          'description' => 'The rating given in this review.',
          'type' => array('Rating'),
        ),
        'image' => array(
          'name' => 'Image',
          'description' => 'Images should be at least 696 pixels wide.',
          'type' => array('ImageObject'),
          'required' => TRUE,
        ),
        'video' => array(
          'name' => 'Video',
          'description' => 'An embedded video object or a video file.',
          'type' => array('VideoObject'),
        ),
        'author' => array(
          'name' => 'Author',
          'description' => 'The creator/author of this review.',
          'type' => array('Person', 'Organization'),
          'required' => TRUE,
        ),
        'datePublished' => array(
          'name' => 'Date published',
          'description' => 'The date and time the article was first published',
          'type' => array('DateTime'),
          'required' => TRUE,
        ),
        'dateModified' => array(
          'name' => 'Date modified',
          'description' => 'The date and time the article was most recently modified',
          'type' => array('DateTime'),
        ),
        'publisher' => array(
          'name' => 'Publisher',
          'description' => 'The publisher of the video.',
          'type' => array('Organization'),
        ),
      ),
    ),
// Video
    'VideoObject' => array(
      'name' => t('Video'),
      'properties' => array(
        'name' => array(
          'name' => 'Name',
          'description' => 'The name of the video.',
          'type' => array('Text'),
          'required' => TRUE,
        ),
        'embedUrl' => array(
          'name' => 'Video embed URL',
          'description' => 'URL for the video file.',
          'type' => array('URL'),
        ),
        'description' => array(
          'name' => 'Description',
          'description' => 'A description of the video.',
          'type' => array('Text'),
        ),
        'thumbnailUrl' => array(
          'name' => 'Thumbnail',
          'description' => 'Thumbnail image for an image or video.',
          'type' => array('ImageObject'),
        ),
        'publisher' => array(
          'name' => 'Publisher',
          'description' => 'The publisher of the video.',
          'type' => array('Organization'),
        ),
      ),
    ),
// Product
    'Product' => array(
      'name' => t('Product'),
      'properties' => array(
        // TODO
        'brand' => array(
          'name' => 'Brand',
          'description' => 'The brand(s) associated with a product or service, or the brand(s) maintained by an organization or business person',
          'type' => array('Brand', 'Organization'),
        ),
      ),
      'hidden' => TRUE,
    ),
// Organization @todo
    'Organization' => array(
      'name' => t('Organization'),
      'properties' => array(),
      'hidden' => TRUE,
    ),
// Person @todo
    'Person' => array(
      'name' => t('Person'),
      'properties' => array(),
      'hidden' => TRUE,
    ),
// @todo
  );

  // Allow schemas to be altered.
  backrop_alter('structured_data_schemas', $schemas);

  if ($type == NULL) {
    return $schemas;
  }
  else {
    return $schemas[$type];
  }
}
